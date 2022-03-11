// do not touch anything below
// unless you know what you're doing

#ifdef WIN32
#error You must build in x64
#endif

#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <string>
#include <thread>
#include <iterator>
#include <algorithm>
#include <cmath>

#include "bindingthread.h"
#include "definitions.h"
#include "config.h"
#include "error.h"

#include "variables.h"

bool bStop = false;
std::string GamePath{};
bool VSyncEnable = false;
int FpsIndex = TARGET_FPS_INDEX;
int FpsOffset = 0;
bool LowPower = false;
bool Enabled = true;
int DefaultFPS = -1;

// didnt made this pattern scan - c+p'd from somewhere
uintptr_t PatternScan(void* module, const char* signature)
{
	static auto pattern_to_byte = [](const char* pattern) {
		auto bytes = std::vector<int>{};
		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current) {
			if (*current == '?') {
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else {
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
		return bytes;
	};

	auto dosHeader = (PIMAGE_DOS_HEADER)module;
	auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

	auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto patternBytes = pattern_to_byte(signature);
	auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

	auto s = patternBytes.size();
	auto d = patternBytes.data();

	for (auto i = 0ul; i < sizeOfImage - s; ++i) {
		bool found = true;
		for (auto j = 0ul; j < s; ++j) {
			if (scanBytes[i + j] != d[j] && d[j] != -1) {
				found = false;
				break;
			}
		}
		if (found) {
			return (uintptr_t)&scanBytes[i];
		}
	}
	return 0;
}


bool GetModule(DWORD pid, std::string ModuleName, PMODULEENTRY32 pEntry)
{
	if (!pEntry)
		return false;

	MODULEENTRY32 mod32{};
	mod32.dwSize = sizeof(mod32);
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	for (Module32First(snap, &mod32); Module32Next(snap, &mod32);)
	{
		if (mod32.th32ProcessID != pid)
			continue;

		if (mod32.szModule == ModuleName)
		{
			*pEntry = mod32;
			break;
		}
	}
	CloseHandle(snap);

	return pEntry->modBaseAddr;
}

void InjectReshade(HANDLE hProcess)
{
	std::string buffer;
	buffer.reserve(GetCurrentDirectoryA(0, nullptr));
	ZeroMemory(buffer.data(), buffer.capacity());
	GetCurrentDirectoryA(buffer.capacity(), buffer.data());

	std::string DLLPath = buffer.c_str() + std::string("\\ReShade64.dll");
	if (GetFileAttributesA(DLLPath.c_str()) == INVALID_FILE_ATTRIBUTES)
		return;

	printf("\nReShade found\n");
	printf("Injecting ReShade...\n");

	LPVOID pPath = VirtualAllocEx(hProcess, nullptr, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!pPath)
	{
		DWORD code = GetLastError();
		printf("VirtualAllocEx failed (%d): %s\n", code, GetLastErrorAsString(code).c_str());
		return;
	}

	WriteProcessMemory(hProcess, pPath, DLLPath.data(), DLLPath.length(), nullptr);

	HANDLE hThread = CreateRemoteThread(hProcess, nullptr, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA,
		pPath, 0, nullptr);
	if (!hThread)
	{
		DWORD code = GetLastError();
		printf("CreateRemoteThread failed (%d): %s\n", code, GetLastErrorAsString(code).c_str());
		return;
	}

	WaitForSingleObject(hThread, -1);
	VirtualFreeEx(hProcess, pPath, 0, MEM_RELEASE);
	CloseHandle(hThread);

	printf("ReShade loaded\n\n");
}

// c&p'd from StackOverflow, obviously
HWND gameHwnd = NULL;
BOOL CALLBACK EnumWindowsProcMy(HWND hwnd, LPARAM lParam) {
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(hwnd, &lpdwProcessId);
	if (lpdwProcessId == lParam)
	{
		gameHwnd = hwnd;
		return FALSE;
	}
	return TRUE;
};

int main(int argc, char** argv)
{
	std::atexit([] {
		system("pause"); 
		});

	SetConsoleTitleA("Genshin FPS Unlocker");

	std::string CommandLine{};
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
			CommandLine += argv[i] + std::string(" ");
	}

	LoadConfig();
	int TargetFPS = DEFAULT_FPS_STEPS[FpsIndex] + FpsOffset;
	std::string ProcessPath = GamePath;
	std::string ProcessDir{};

	printf("FPS Unlocker " VERSION "\n");
	printf("Game: %s\n\n", ProcessPath.c_str());
	ProcessDir = ProcessPath.substr(0, ProcessPath.find_last_of("\\"));

	printf("Available FPS:");
	std::for_each(std::begin(DEFAULT_FPS_STEPS), std::end(DEFAULT_FPS_STEPS), [](const int& v) { printf(" %d", v); });
	puts("\n");

	STARTUPINFOA si{};
	PROCESS_INFORMATION pi{};
	if (!CreateProcessA(ProcessPath.c_str(), (LPSTR)CommandLine.c_str(), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi))
	{
		DWORD code = GetLastError();
		printf("CreateProcess failed (%d): %s\n", code, GetLastErrorAsString(code).c_str());
		return 0;
	}

	CloseHandle(pi.hThread);
	printf("PID: %d\n", pi.dwProcessId);

	MODULEENTRY32 hUnityPlayer{};
	while (!GetModule(pi.dwProcessId, "UnityPlayer.dll", &hUnityPlayer))
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	InjectReshade(pi.hProcess);

	printf("UnityPlayer: %X%X\n", (uintptr_t)hUnityPlayer.modBaseAddr >> 32 & -1, hUnityPlayer.modBaseAddr);

	LPVOID mem = VirtualAlloc(nullptr, hUnityPlayer.modBaseSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!mem)
	{
		DWORD code = GetLastError();
		printf("VirtualAlloc failed (%d): %s\n", code, GetLastErrorAsString(code).c_str());
		return 0;
	}

	ReadProcessMemory(pi.hProcess, hUnityPlayer.modBaseAddr, mem, hUnityPlayer.modBaseSize, nullptr);

	printf("Searching for pattern...\n");
	/*
		 7F 0F              jg   0x11
		 8B 05 ? ? ? ?      mov eax, dword ptr[rip+?]
	*/
	uintptr_t address = PatternScan(mem, "7F 0F 8B 05 ? ? ? ?");
	if (!address)
	{
		printf("outdated pattern\n");
		return 0;
	}

	// calculate the offset to where the fps value is stored
	uintptr_t pfps = 0;
	{
		uintptr_t rip = address + 2;
		uint32_t rel = *(uint32_t*)(rip + 2);
		pfps = rip + rel + 6;
		pfps -= (uintptr_t)mem;
		printf("FPS Offset: %X\n", pfps);
		pfps = (uintptr_t)hUnityPlayer.modBaseAddr + pfps;
	}

	// calculate where vsync value is stored
	address = PatternScan(mem, "E8 ? ? ? ? 8B E8 49 8B 1E");
	uintptr_t pvsync = 0;
	if (address)
	{
		uintptr_t ppvsync = 0;
		uintptr_t rip = address;
		int32_t rel = *(int32_t*)(rip + 1);
		rip = rip + rel + 5;
		uint64_t rax = *(uint32_t*)(rip + 3);
		ppvsync = rip + rax + 7;
		ppvsync -= (uintptr_t)mem;
		printf("VSync Offset: %X\n", ppvsync);
		ppvsync = (uintptr_t)hUnityPlayer.modBaseAddr + ppvsync;

		uintptr_t buffer = 0;
		while (!buffer)
		{
			ReadProcessMemory(pi.hProcess, (LPCVOID)ppvsync, &buffer, sizeof(buffer), nullptr);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		rip += 7;
		pvsync = *(uint32_t*)(rip + 2);
		pvsync = buffer + pvsync;
	}

	VirtualFree(mem, 0, MEM_RELEASE);
	printf("Done\n\n");

	printf("Use Home + arrow keys to change the FPS cap:\n");
	printf("  HOME+UP:    Increase the cap\n");
	printf("  HOME+DOWN:  Decrease the cap\n");
	printf("  HOME+LEFT:  Decrease the cap by %dfps\n", SMALL_STEP);
	printf("  HOME+RIGHT: Increase the cap by %dfps\n", BIG_STEP);
	printf("  HOME+END:   Toggle on/off\n\n");

	// keybinds thread
	HANDLE hThread = CreateThread(nullptr, 0, Thread1, &TargetFPS, 0, nullptr);

	// set gameHWND
	EnumWindows(EnumWindowsProcMy, pi.dwProcessId);

	DWORD ExitCode = STILL_ACTIVE;
	while (ExitCode == STILL_ACTIVE)
	{
		GetExitCodeProcess(pi.hProcess, &ExitCode);

		//const auto foregroundHwnd = GetForegroundWindow();
		LowPower = GetForegroundWindow() != gameHwnd;

		// runs a check every 2 seconds. 
		std::this_thread::sleep_for(std::chrono::seconds(2));

		int fps = 0; 
		ReadProcessMemory(pi.hProcess, (LPVOID)pfps, &fps, sizeof(fps), nullptr);
		if (fps == -1) 
			continue;
		if (DefaultFPS == -1)
			DefaultFPS = fps;
		const auto targetFPS = Enabled ?
			(LowPower ? DEFAULT_FPS_STEPS[POWER_SAVING_FPS_INDEX] : TargetFPS) : DefaultFPS;
		if (fps != targetFPS)
			WriteProcessMemory(pi.hProcess, (LPVOID)pfps, &targetFPS, sizeof(targetFPS), nullptr);

		int vsync = 0;
		ReadProcessMemory(pi.hProcess, (LPVOID)pvsync, &vsync, sizeof(vsync), nullptr);
		if (vsync && !VSyncEnable)
		{
			vsync = 0;
			// disable vsync
			WriteProcessMemory(pi.hProcess, (LPVOID)pvsync, &vsync, sizeof(vsync), nullptr);
		}
	}

	bStop = true;
	WaitForSingleObject(hThread, -1);
	CloseHandle(hThread);
	CloseHandle(pi.hProcess);
	TerminateProcess((HANDLE)-1, 0);

	return 0;
}
