#pragma once
#include <Windows.h>
#include <string>
#include <TlHelp32.h>
#include <Psapi.h>
#include <vector>
#include "Settings.h"

namespace Unmanaged
{
	inline bool InBackground = false;
	inline bool UsePowerSave = false;
	inline HWINEVENTHOOK EventHook = nullptr;
	inline HANDLE GameHandle = nullptr;
	inline DWORD GamePID = 0;
	inline DWORD StartPriority = 0;
	inline uintptr_t pFPSValue = 0;
	inline uintptr_t pVSyncValue = 0;
	inline const std::vector<DWORD> PrioityClass = {
		REALTIME_PRIORITY_CLASS,
		HIGH_PRIORITY_CLASS,
		ABOVE_NORMAL_PRIORITY_CLASS,
		NORMAL_PRIORITY_CLASS,
		BELOW_NORMAL_PRIORITY_CLASS,
		IDLE_PRIORITY_CLASS
	};

	void __stdcall WinEventProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD idEventThread, DWORD dwmsEventTime);

	bool StartProcess(LPCSTR ProcessPath, LPSTR CommandLine, int Priority);
	bool IsGameRunning();
	bool GetModule(DWORD pid, std::string ModuleName, PMODULEENTRY32 pEntry);
	bool SetupData();
	bool ShowError(std::string apiName, DWORD code);
	bool VerifyDLL(PVOID module);

	DWORD GetPID(std::string ProcessName);
	uintptr_t PatternScan(PVOID module, LPCSTR signature);

	std::string GetGamePath();
	std::string GetLastErrorAsString(DWORD code);

	void ApplyFPS(int fps, bool powerSave);
	void ApplyFPSImpl(int fps);
	void ApplyVSync(bool disable);
	void InjectDLLs(std::vector<std::string> paths);
}