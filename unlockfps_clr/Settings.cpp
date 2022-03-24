#include "Settings.h"

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Text::Json;
using namespace System::Windows::Forms;

Settings::Settings()
{
    
}

Settings^ Settings::InitializeDefaults()
{
    GamePath = "";

    AutoStart = false;
    AutoDisableVSync = true;
    PopupWindow = false;
    Fullscreen = false;
    UseCustomRes = false;
    IsExclusiveFullscreen = false;
    UsePowerSave = false;

    FPSTarget = 120;
    CustomResX = 1920;
    CustomResY = 1080;
    Priority = 3;

    DllList = gcnew List<String^>();

    return this;
}

void Settings::Save()
{
    auto options = gcnew JsonSerializerOptions();
    options->WriteIndented = true;

    auto serialized = JsonSerializer::Serialize(this, options);
    File::WriteAllText(ConfigPath, serialized, Encoding::UTF8);
}

Settings^ Settings::Load()
{
    // create a config if there isn't one
    if (!File::Exists(ConfigPath))
        return (gcnew Settings())->InitializeDefaults();

    auto serialized = File::ReadAllText(ConfigPath, Encoding::UTF8);
    Settings^ instance = JsonSerializer::Deserialize<Settings^>(serialized, nullptr);

    // extra sanitization
    if (!instance->DllList)
        instance->DllList = gcnew List<String^>();

    // remove invalid items
    for each (auto path in instance->DllList->ToArray())
    {
        if (!File::Exists(path))
            instance->DllList->Remove(path);
    }

    return instance;
}
