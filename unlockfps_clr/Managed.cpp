#include "Unmanaged.h"
#include "Managed.h"

List<String^>^ Managed::TryResolveGamePath()
{
    List<String^>^ result = gcnew List<String^>{};
    auto RazerChromaSDK = Registry::LocalMachine->OpenSubKey("SOFTWARE\\WOW6432Node\\Razer Chroma SDK\\Apps");

    if (RazerChromaSDK && RazerChromaSDK->SubKeyCount)
    {
        auto SubKeys = RazerChromaSDK->GetSubKeyNames();
        for each(auto it in SubKeys)
        {
            auto SubKeyName = it;
            if (!SubKeyName->Contains("GenshinImpact") && !SubKeyName->Contains("YuanShen"))
                continue;

            auto SubKey = RazerChromaSDK->OpenSubKey(SubKeyName);
            if (!SubKey)
                continue;

            auto Path = static_cast<String^>(SubKey->GetValue("Path"));
            if (String::IsNullOrWhiteSpace(Path))
                continue;

            if (!File::Exists(Path))
                continue;

            Path = Path->Replace("/", "\\");
            result->Add(Path);
        }

        if (result->Count)
            return result;
    }

    // cannot find anything through chroma sdk
    // use uninstall list instead

    auto Uninstall = Registry::LocalMachine->OpenSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
    if (Uninstall && Uninstall->SubKeyCount)
    {
        auto SubKeys = Uninstall->GetSubKeyNames();
        for each (auto it in SubKeys)
        {
            auto SubKeyName = it;
            if (!SubKeyName->Contains("Genshin Impact") && !SubKeyName->Contains(L"Ô­Éñ"))
                continue;

            auto SubKey = Uninstall->OpenSubKey(SubKeyName);
            if (!SubKey)
                continue;

            // the install path is the official launcher path
            auto InstallPath = static_cast<String^>(SubKey->GetValue("InstallPath"));
            if (String::IsNullOrWhiteSpace(InstallPath))
                continue;

            if (!Directory::Exists(InstallPath))
                continue;

            String^ LauncherConfigPath = InstallPath + "\\config.ini";
            if (!File::Exists(LauncherConfigPath))
                continue;

            // read the official launcher config
            // it contains the game install path and exe name
            auto LauncherConfig = File::ReadAllLines(LauncherConfigPath);
            Dictionary<String^, String^>^ ini = gcnew Dictionary<String^, String^>();
            for each (auto Line in LauncherConfig)
            {
                auto split = Line->Split(gcnew array<String^>{"="}, StringSplitOptions::RemoveEmptyEntries);
                if (split->Length < 2)
                    continue;

                ini[split[0]] = split[1];
            }

            result->Add(String::Format("{0}/{1}", ini["game_install_path"], ini["game_start_name"])->Replace("/", "\\"));
        }

        return result;
    }

    return result;
}

String^ Managed::TryGetGamePath()
{
    auto path = Unmanaged::GetGamePath();
    return gcnew String(path.c_str());
}

void Managed::InjectDLLs(List<String^>^ paths)
{
    if (!paths->Count)
        return;

    std::vector<std::string> stlPaths;
    
    for each (auto path in paths)
    {
        LPSTR nativeString = static_cast<LPSTR>(static_cast<PVOID>(Marshal::StringToHGlobalAnsi(path)));
        stlPaths.push_back(nativeString);
        Marshal::FreeHGlobal(static_cast<IntPtr>(nativeString));
    }

    Unmanaged::InjectDLLs(stlPaths);
}

bool Managed::StartGame(Settings^ settings)
{
    if (Unmanaged::IsGameRunning() || Unmanaged::GetPID("GenshinImpact.exe") || Unmanaged::GetPID("YuanShen.exe"))
    {
        MessageBox::Show("An instance of the game is already running", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
        return false;
    }

    String^ commandLine = "";

    if (settings->PopupWindow)
        commandLine += "-popupwindow ";
    if (settings->UseCustomRes)
        commandLine += String::Format("-screen-width {0} -screen-height {1} ", settings->CustomResX, settings->CustomResY);

    commandLine += String::Format("-screen-fullscreen {0} ", Convert::ToInt32(settings->Fullscreen));
    commandLine += String::Format("-window-mode {0} ", settings->IsExclusiveFullscreen ? "exclusive" : "borderless");
    commandLine += String::Format("-monitor {0} ", settings->MonitorNum);

    LPSTR nativeCommandLine = static_cast<LPSTR>(static_cast<PVOID>(Marshal::StringToHGlobalAnsi(commandLine)));
    LPSTR nativeGamePath = static_cast<LPSTR>(static_cast<PVOID>(Marshal::StringToHGlobalAnsi(settings->GamePath)));

    auto result = Unmanaged::StartProcess(nativeGamePath, nativeCommandLine, settings->Priority);

    Marshal::FreeHGlobal(static_cast<IntPtr>(nativeCommandLine));
    Marshal::FreeHGlobal(static_cast<IntPtr>(nativeGamePath));

    return result;
}
