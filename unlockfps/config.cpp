#include "config.h"

#include <thread>
#include <cstdio>
#include <TlHelp32.h>
#include "error.h"
#include "keybind.h"

std::string Config::gamePath;
int Config::fps;
std::vector<int> Config::fpsCaps;
bool Config::powerSavingEnabled;
int Config::powerSavingFps;
int Config::powerSavingDelay;
bool Config::vsync;

int Config::comboKey;
int Config::toggleKey;
int Config::increaseKey;
int Config::increaseSmallKey;
int Config::decreaseKey;
int Config::decreaseSmallKey;

Config::Init Config::init;

DWORD Config::GetPID(std::string ProcessName)
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

bool Config::WriteConfig()
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
	content += INI_KEY_POWER_SAVING_ENABLED "=" + std::to_string(powerSavingEnabled) + "\n";
	content += INI_KEY_POWER_SAVING_FPS "=" + std::to_string(powerSavingFps) + "\n";
	content += INI_KEY_DELAY "=" + std::to_string(powerSavingDelay) + "\n";
	content += INI_KEY_FPS_CAPS "=" + GetFpsCapsStr() + "\n";
	content += INI_KEY_VSYNC "=" + std::to_string(vsync) + "\n";

	content += "\n";

	content += "[" INI_SECTION_KEY_BINDING "]\n";
	content += INI_KEY_COMBO "=" + KeyBind::GetVKString(comboKey) + "\n";
	content += INI_KEY_TOGGLE "=" + KeyBind::GetVKString(toggleKey) + "\n";
	content += INI_KEY_INCREASE "=" + KeyBind::GetVKString(increaseKey) + "\n";
	content += INI_KEY_INCREASE_SMALL "=" + KeyBind::GetVKString(increaseSmallKey) + "\n";
	content += INI_KEY_DECREASE "=" + KeyBind::GetVKString(decreaseKey) + "\n";
	content += INI_KEY_DECREASE_SMALL "=" + KeyBind::GetVKString(decreaseSmallKey) + "\n";

	DWORD written = 0;
	WriteFile(hFile, content.data(), content.size(), &written, nullptr);
	CloseHandle(hFile);
}

void Config::CreateConfig(const INIReader& reader)
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

void Config::LoadConfig()
{
	if (INIReader reader(CONFIG_FILE); reader.ParseError() != 0)
	{
		// default values.
		comboKey = KEY_COMBO;
		toggleKey = KEY_TOGGLE;
		increaseKey = KEY_INCREASE;
		increaseSmallKey = KEY_INCREASE_SMALL;
		decreaseKey = KEY_DECREASE;
		decreaseSmallKey = KEY_DECREASE_SMALL;

		fps = D_TARGET_FPS;
		SetFpsCaps(D_FPS_CAPS);
		powerSavingEnabled = D_POWER_SAVING_ENABLED;
		powerSavingFps = D_POWER_SAVING_FPS;
		powerSavingDelay = D_POWER_SAVING_DELAY;
		vsync = D_VSYNC;

		// Create and save the config file.
		CreateConfig(reader);
	}
	else 
	{
		gamePath = reader.Get(INI_SECTION_SETTING, INI_KEY_PATH, "");

		SetFps(reader.GetInteger(INI_SECTION_SETTING, INI_KEY_FPS, D_TARGET_FPS));

		SetFpsCaps(reader.Get(INI_SECTION_SETTING, INI_KEY_FPS_CAPS, D_FPS_CAPS));
		std::sort(fpsCaps.begin(), fpsCaps.end());

		powerSavingEnabled = reader.GetInteger(INI_SECTION_SETTING, INI_KEY_POWER_SAVING_ENABLED, D_POWER_SAVING_ENABLED);
		SetPowerSavingFps(reader.GetInteger(INI_SECTION_SETTING, INI_KEY_POWER_SAVING_FPS, D_POWER_SAVING_FPS));
		SetPowerSavingDelay(reader.GetInteger(INI_SECTION_SETTING, INI_KEY_DELAY, D_POWER_SAVING_DELAY));

		vsync = reader.GetInteger(INI_SECTION_SETTING, INI_KEY_VSYNC, D_VSYNC);

		const auto ckText = reader.Get(INI_SECTION_KEY_BINDING, INI_KEY_COMBO, std::to_string(KEY_COMBO));
		comboKey = KeyBind::GetValue(ckText);
		
		const auto tkText = reader.Get(INI_SECTION_KEY_BINDING, INI_KEY_TOGGLE, std::to_string(KEY_TOGGLE));
		toggleKey = KeyBind::GetValue(tkText);
		
		const auto ikText = reader.Get(INI_SECTION_KEY_BINDING, INI_KEY_INCREASE, std::to_string(KEY_INCREASE));
		increaseKey = KeyBind::GetValue(ikText);
		const auto sikText = reader.Get(INI_SECTION_KEY_BINDING, INI_KEY_INCREASE_SMALL, std::to_string(KEY_INCREASE_SMALL));
		increaseSmallKey = KeyBind::GetValue(sikText);

		const auto dkText = reader.Get(INI_SECTION_KEY_BINDING, INI_KEY_DECREASE, std::to_string(KEY_DECREASE));
		decreaseKey = KeyBind::GetValue(dkText);
		const auto sdkText = reader.Get(INI_SECTION_KEY_BINDING, INI_KEY_DECREASE_SMALL, std::to_string(KEY_DECREASE_SMALL));
		decreaseSmallKey = KeyBind::GetValue(sdkText);

		if (GetFileAttributesA(gamePath.c_str()) == INVALID_FILE_ATTRIBUTES)
		{
			printf("Looks like you've moved your game somewhere else - Lets setup again\n");
			DeleteFileA(CONFIG_FILE);
			LoadConfig();
		}
	}
}
