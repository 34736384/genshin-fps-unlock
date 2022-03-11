#include "config.h"

#include <thread>
#include <cstdio>
#include <TlHelp32.h>
#include "error.h"
#include "inireader.h"
#include "variables.h"

DWORD GetPID(std::string ProcessName)
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

bool WriteConfig(std::string GamePath, int fpsIndex, int fpsOffset, int VSyncEnable)
{
	HANDLE hFile = CreateFileA("fps_config.ini", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ,
		nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		DWORD code = GetLastError();
		printf("CreateFileA failed (%d): %s\n", code, GetLastErrorAsString(code).c_str());
		return false;
	}

	std::string content{};
	content = "[Setting]\n";
	content += "Path=" + GamePath + "\n";
	content += "FPSIndex=" + std::to_string(fpsIndex) + "\n";
	content += "FPSOffset=" + std::to_string(fpsOffset) + "\n";
	content += "VSYNC=" + std::to_string(VSyncEnable);

	DWORD written = 0;
	WriteFile(hFile, content.data(), content.size(), &written, nullptr);
	CloseHandle(hFile);
}

void LoadConfig()
{
	INIReader reader("fps_config.ini");
	if (reader.ParseError() != 0)
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

		GamePath = szPath;
		WriteConfig(GamePath, FpsIndex, FpsOffset, VSyncEnable);

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
		return;
	}

	GamePath = reader.Get("Setting", "Path", "");
	FpsIndex = reader.GetInteger("Setting", "FPSIndex", FpsIndex);
	FpsOffset = reader.GetInteger("Setting", "FPSOffset", FpsOffset);
	VSyncEnable = reader.GetInteger("Setting", "VSYNC", VSyncEnable);

	if (GetFileAttributesA(GamePath.c_str()) == INVALID_FILE_ATTRIBUTES)
	{
		printf("Looks like you've moved your game somewhere else - Lets setup again\n");
		DeleteFileA("fps_config.ini");
		LoadConfig();
	}
}
