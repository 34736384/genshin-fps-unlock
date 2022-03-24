#pragma once
using namespace System;
using namespace System::Collections::Generic;

[Serializable]
public ref class Settings
{
private:
	static String^ ConfigPath = "fps_config.json";
public:
	property String^ GamePath;

	property bool AutoStart;
	property bool AutoDisableVSync;
	property bool AutoClose;
	property bool PopupWindow;
	property bool Fullscreen;
	property bool UseCustomRes;
	property bool IsExclusiveFullscreen;
	property bool StartMinimized;
	property bool UsePowerSave;

	property int FPSTarget;
	property int CustomResX;
	property int CustomResY;
	property int MonitorNum;
	property int Priority;

	property List<String^>^ DllList;

	Settings();
	Settings^ InitializeDefaults();
	void Save();
	static Settings^ Load();
};