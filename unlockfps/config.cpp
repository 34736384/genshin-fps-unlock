#include "config.h"

#include <thread>
#include <cstdio>
#include <TlHelp32.h>
#include "error.h"

std::string Configurator::gamePath;
int Configurator::fps;
std::vector<int> Configurator::fpsCaps;
int Configurator::powerSavingFps;
bool Configurator::vsync;

Configurator::Initializer Configurator::initializer;

DWORD Configurator::GetPID(std::string ProcessName)
{
	DWORD pid = 0;
	PROCESSENTRY32 pe32{};
	pe32.dwSize = sizeof(pe32);
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	for (Process32First(snap, &pe32); Process32Next(snap, &pe32);)
	{
		if (pe32.szExeFile == ProcessName)
		{
			pid = pe32.th32ProcessID;
			break;
		}
	}
	CloseHandle(snap);
	return pid;
}

bool Configurator::WriteConfig()
{
	HANDLE hFile = CreateFileA(CONFIG_FILE, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
		nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		DWORD code = GetLastError();
		printf("CreateFileA failed (%d): %s\n", code, GetLastErrorAsString(code).c_str());
		return false;
	}

	std::string content{};
	content = "[" INI_SECTION_SETTING "]\n";
	content += INI_KEY_PATH "=" + gamePath + "\n";
	content += INI_KEY_FPS "=" + std::to_string(fps) + "\n";
	content += INI_KEY_POWER_SAVING_FPS "=" + std::to_string(powerSavingFps) + "\n";
	content += INI_KEY_FPS_CAPS "=" + fpsCaps2str() + "\n";
	content += INI_KEY_VSYNC "=" + std::to_string(vsync);

	DWORD written = 0;
	WriteFile(hFile, content.data(), content.size(), &written, nullptr);
	CloseHandle(hFile);
}

void Configurator::createConfig(const INIReader &reader)
{
	printf("Config not found - Starting first time setup\nPlease leave this open and start the game\n"
		"This only need to be done once\n\n");
	printf("Waiting for game...\n");

	DWORD pid = 0;
	while (!(pid = GetPID("YuanShen.exe")) && !(pid = GetPID("GenshinImpact.exe")))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | SYNCHRONIZE, FALSE, pid);

	char szPath[MAX_PATH]{};
	DWORD length = sizeof(szPath);
	QueryFullProcessImageNameA(hProcess, 0, szPath, &length);

	gamePath = szPath;
	WriteConfig();

	HWND hwnd = nullptr;
	while (!(hwnd = FindWindowA("UnityWndClass", nullptr)))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	DWORD ExitCode = STILL_ACTIVE;
	while (ExitCode == STILL_ACTIVE)
	{
		SendMessageA(hwnd, WM_CLOSE, 0, 0);
		GetExitCodeProcess(hProcess, &ExitCode);
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

	// wait for the game to close then continue
	WaitForSingleObject(hProcess, -1);
	CloseHandle(hProcess);

	system("cls");
}

void Configurator::LoadConfig()
{
	if (INIReader reader(CONFIG_FILE); reader.ParseError() != 0)
		createConfig(reader);
	else {
		gamePath = reader.Get(INI_SECTION_SETTING, INI_KEY_PATH, "");
		fps = reader.GetInteger(INI_SECTION_SETTING, INI_KEY_FPS, fps);
		str2fpsCaps(reader.Get(INI_SECTION_SETTING, INI_KEY_FPS_CAPS, DEFAULT_FPS_CAPS));
		std::sort(fpsCaps.begin(), fpsCaps.end());
		powerSavingFps = reader.GetInteger(INI_SECTION_SETTING, INI_KEY_POWER_SAVING_FPS, powerSavingFps);

		vsync = reader.GetInteger("Setting", "VSYNC", vsync);

		if (GetFileAttributesA(gamePath.c_str()) == INVALID_FILE_ATTRIBUTES)
		{
			printf("Looks like you've moved your game somewhere else - Lets setup again\n");
			DeleteFileA(CONFIG_FILE);
			LoadConfig();
		}
	}
}
