#define KEY_TOGGLE VK_END
#define KEY_INCREASE VK_UP
#define KEY_DECREASE VK_DOWN
#define FPS_TARGET 120

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
#include <filesystem>

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

std::string GetLastErrorAsString(DWORD code)
{
    LPSTR buf = nullptr;
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buf, 0, NULL);
    std::string ret = buf;
    LocalFree(buf);
    return ret;
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

bool SearchForGame(std::string& out)
{
    auto CurrentPath = std::filesystem::current_path();
    for (auto& p : std::filesystem::directory_iterator(CurrentPath))
    {
        if (!p.is_directory())
            continue;

        for (auto& pp : std::filesystem::directory_iterator(p))
        {
            if (pp.is_directory())
                continue;

            auto path = pp.path().string();
            if (path.find("YuanShen.exe") != std::string::npos ||
                path.find("GenshinImpact.exe") != std::string::npos)
            {
                out = path;
                return true;
            }
        }
    }
    return false;
}

DWORD __stdcall Thread1(LPVOID p)
{
    if (!p)
        return 0;

    int* pTargetFPS = (int*)p;
    int fps = *pTargetFPS;
    int prev = fps;
    while (true)
    {
        if (GetAsyncKeyState(KEY_DECREASE) & 1)
            fps -= 20;
        if (GetAsyncKeyState(KEY_INCREASE) & 1)
            fps += 20;
        if (GetAsyncKeyState(KEY_TOGGLE) & 1)
            fps = fps != 60 ? 60 : prev;
        if (fps > 60)
            prev = fps;
        if (fps < 60)
            fps = 60;
        printf("\rFPS: %d - %s    ", fps, fps > 60 ? "ON" : "OFF");
        *pTargetFPS = fps;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}

int main()
{
    std::atexit([] {
        system("pause");
    });

    SetConsoleTitleA("");
    int TargetFPS = FPS_TARGET;

    // seach for the game in subfolders
    std::string ProcessPath{};
    std::string ProcessDir{};
    if (!SearchForGame(ProcessPath))
    {
        printf("Game not found in any subfolders - did you put the unlocker in the right place?\n");
        return 0;
    }
    printf("Game: %s\n\n", ProcessPath.c_str());
    ProcessDir = ProcessPath.substr(0, ProcessPath.find_last_of("\\"));

    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    if (!CreateProcessA(ProcessPath.c_str(), nullptr, nullptr, nullptr, FALSE, 0, nullptr, ProcessDir.c_str(), &si, &pi))
    {
        DWORD code = GetLastError();
        printf("CreateProcess failed (%d): %s", code, GetLastErrorAsString(code).c_str());
        return 0;
    }

    CloseHandle(pi.hThread);
    printf("PID: %d\n", pi.dwProcessId);

    MODULEENTRY32 hUnityPlayer{};
    // wait for UnityPlayer.dll to load
    while (!GetModule(pi.dwProcessId, "UnityPlayer.dll", &hUnityPlayer))
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    printf("UnityPlayer: %X%X\n", (uintptr_t)hUnityPlayer.modBaseAddr >> 32 & -1, hUnityPlayer.modBaseAddr);

    LPVOID mem = VirtualAlloc(nullptr, hUnityPlayer.modBaseSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!mem)
    {
        DWORD code = GetLastError();
        printf("VirtualAlloc failed (%d): %s", code, GetLastErrorAsString(code).c_str());
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

    // calcuate the offset to where the fps value is stored
    uintptr_t rip = address + 2;
    uint32_t rel = *(uint32_t*)(rip + 2);
    uintptr_t offset = rip + rel + 6;
    offset -= (uintptr_t)mem;
    printf("Offset: %X\n", offset);
    offset = (uintptr_t)hUnityPlayer.modBaseAddr + offset;

    VirtualFree(mem, 0, MEM_RELEASE);
    printf("Done\n\n");

    // keybinds thread
    HANDLE hThread = CreateThread(nullptr, 0, Thread1, &TargetFPS, 0, nullptr);
    if (hThread)
        CloseHandle(hThread);

    while (true)
    {
        // runs a check every 2 seconds
        std::this_thread::sleep_for(std::chrono::seconds(2));
        int fps = 0;
        ReadProcessMemory(pi.hProcess, (LPVOID)offset, &fps, sizeof(fps), nullptr);
        if (fps == -1)
            continue;
        if (fps != TargetFPS)
            WriteProcessMemory(pi.hProcess, (LPVOID)offset, &TargetFPS, sizeof(TargetFPS), nullptr);
    }

    CloseHandle(pi.hProcess);

    return 0;
}