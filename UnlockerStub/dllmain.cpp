// ReSharper disable CppClangTidyMiscUseInternalLinkage
#include <Windows.h>
#include <DbgHelp.h>
#include <ranges>
#include <algorithm>
#include "Utils.h"

#pragma comment(lib, "dbghelp.lib")
#pragma comment(lib, "ntdll.lib")
EXTERN_C NTSTATUS __stdcall LdrAddRefDll(ULONG Flags, PVOID BaseAddress);

namespace
{
	HMODULE ModuleBase = nullptr;
	int32_t* pFramerate = nullptr;
	HWND GameWindow = nullptr;

	enum class IPCStatus : int8_t
	{
		None,
		Error,
		Ready
	};

	struct __declspec(align(8)) IPCData
	{
		IPCStatus Status;
		int32_t Framerate;
		bool PowerSave;
	};

}

LONG __stdcall VectoredExceptionHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
	const auto exceptionRecord = ExceptionInfo->ExceptionRecord;

	HMODULE hModule = nullptr;
	GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, static_cast<LPCSTR>(exceptionRecord->ExceptionAddress), &hModule);
	
	if (hModule == ModuleBase && 
		(exceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION || exceptionRecord->ExceptionCode == EXCEPTION_ILLEGAL_INSTRUCTION || exceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW))
	{

		MINIDUMP_EXCEPTION_INFORMATION dumpInfo{};
		dumpInfo.ThreadId = GetCurrentThreadId();
		dumpInfo.ExceptionPointers = ExceptionInfo;
		dumpInfo.ClientPointers = TRUE;

		const auto hFile = CreateFileW(L"crashdump.dmp", GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &dumpInfo, nullptr, nullptr);
		CloseHandle(hFile);

		Utils::ShowError(L"An unhandled exception has occurred, a crash dump has been saved to crashdump.dmp");
		ExitThread(1);
	}

	return EXCEPTION_CONTINUE_SEARCH;
}

bool SetupData()
{

	const auto imageBase = reinterpret_cast<uint8_t*>(GetModuleHandleA(nullptr));
	const auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(imageBase);
	const auto ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(imageBase + dosHeader->e_lfanew);

	std::span sections{ IMAGE_FIRST_SECTION(ntHeaders), ntHeaders->FileHeader.NumberOfSections };
	std::span<uint8_t> il2cppSection{};
	for (const auto& section : sections)
	{
		if (std::string_view(reinterpret_cast<const char*>(section.Name)) == "il2cpp")
		{
			il2cppSection = { imageBase + section.VirtualAddress, section.Misc.VirtualSize };
			break;
		}
	}

	if (il2cppSection.empty())
	{
		Utils::ShowError(L"Failed to find il2cpp section");
		return false;
	}

	const auto patternResults = Utils::PatternScanAll(il2cppSection, "B9 3C 00 00 00 E8");
	auto targetEntry = std::ranges::filter_view(patternResults, [](const auto& result) { 
		const auto rip = result + 5;
		const auto disp = *reinterpret_cast<int32_t*>(rip + 1);
		const auto dest = rip + disp + 5;
		return *dest == 0xE9;
	}) | std::ranges::views::take(1);

	if (targetEntry.empty())
	{
		Utils::ShowError(L"outdated pattern");
		return false;
	}

	auto rip = targetEntry.front() + 5;
	while (rip[0] == 0xE8 || rip[0] == 0xE9)
	{
		const auto disp = *reinterpret_cast<int32_t*>(rip + 1);
		rip += disp + 5;
	}

	const auto disp = *reinterpret_cast<int32_t*>(rip + 2);
	pFramerate = reinterpret_cast<int32_t*>(rip + disp + 6);

	MEMORY_BASIC_INFORMATION mbi{};
	VirtualQuery(pFramerate, &mbi, sizeof(mbi));

	if (mbi.Protect != PAGE_READWRITE)
	{
		Utils::ShowError(L"invalid address");
		return false;
	}

	return true;
}

HWND GetGameWindow()
{

	EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
	{
		char className[256]{};
		const auto cbReturned = GetClassNameA(hwnd, className, sizeof(className));

		DWORD pid = 0;
		GetWindowThreadProcessId(hwnd, &pid);
		if (pid == GetCurrentProcessId() && std::string_view(className, cbReturned) == "UnityWndClass")
		{
			GameWindow = hwnd;
			return FALSE;
		}
		return TRUE;
	}, 0);

	return GameWindow;
}

DWORD __stdcall ThreadProc(LPVOID lpParameter)
{
	const auto processName = Utils::GetModulePath(nullptr);
	if (!processName.contains(L"YuanShen.exe") && !processName.contains(L"GenshinImpact.exe"))
		return 0;

	const auto processDirectory = processName.substr(0, processName.find_last_of(L'\\'));
	SetCurrentDirectoryW(processDirectory.c_str());

	LdrAddRefDll(1, lpParameter);
	//AddVectoredExceptionHandler(1, VectoredExceptionHandler);

	constexpr auto szGuid = "Global\\2DE95FDC-6AB7-4593-BFE6-760DD4AB422B";
	const auto hMapFile = HandleGuard(OpenFileMappingA(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, szGuid), CloseHandle);
	if (!hMapFile)
	{
		Utils::ShowWin32Error(L"OpenFileMappingA");
		return 0;
	}

	const auto lpView = MappedMemoryGuard(MapViewOfFile(hMapFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0), UnmapViewOfFile);
	if (!lpView)
	{
		Utils::ShowWin32Error(L"MapViewOfFile");
		return 0;
	}

	const auto ipcData = static_cast<IPCData*>(lpView.Get());

	if (!SetupData())
	{
		ipcData->Status = IPCStatus::Error;
		return 0;
	}

	ipcData->Status = IPCStatus::Ready;

	while (true)
	{
		int32_t targetFramerate = ipcData->Framerate;

		if (!GameWindow)
			GameWindow = GetGameWindow();

		if (GameWindow && ipcData->PowerSave)
		{
			if (GetForegroundWindow() != GameWindow)
				targetFramerate = 10;
		}

		targetFramerate = std::clamp(targetFramerate, 10, 1000);
		*pFramerate = targetFramerate;
		Sleep(62);
	}

	return 0;
}

BOOL __stdcall DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpReserved)
{
	ModuleBase = hInstance;

	if (hInstance)
		DisableThreadLibraryCalls(hInstance);

	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		if (const auto hThread = CreateThread(nullptr, 0, ThreadProc, hInstance, 0, nullptr))
			CloseHandle(hThread);
	}

	return TRUE;
}

EXTERN_C __declspec(dllexport) LRESULT __stdcall WndProc(int code, WPARAM wParam, LPARAM lParam)
{
	return CallNextHookEx(nullptr, code, wParam, lParam);
}
