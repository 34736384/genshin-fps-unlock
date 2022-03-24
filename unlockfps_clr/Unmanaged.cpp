#include "Unmanaged.h"
#include <thread>

#pragma comment(lib, "user32.lib")

#pragma unmanaged

void __stdcall Unmanaged::WinEventProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD idEventThread, DWORD dwmsEventTime)
{
    // event handler for monitoring window change
    if (event != EVENT_SYSTEM_FOREGROUND)
        return;

    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);

    if (pid == GamePID)
    {
        InBackground = false;
        ApplyFPSImpl(120);
        SetPriorityClass(GameHandle, StartPriority);
    }
    else if (UsePowerSave)
    {
        InBackground = true;
        ApplyFPSImpl(10);
        SetPriorityClass(GameHandle, IDLE_PRIORITY_CLASS);
    }

}

bool Unmanaged::StartProcess(LPCSTR ProcessPath, LPSTR CommandLine, int Priority)
{
    std::string CurrentDirectory = ProcessPath;
    CurrentDirectory = CurrentDirectory.substr(0, CurrentDirectory.find_last_of('\\'));

    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};

    if (!CreateProcessA(ProcessPath, CommandLine, nullptr, nullptr, FALSE, 0, nullptr, CurrentDirectory.c_str(), &si, &pi))
        return ShowError("CreateProcessA", GetLastError());

    GameHandle = pi.hProcess;
    GamePID = pi.dwProcessId;
    CloseHandle(pi.hThread);

    StartPriority = PrioityClass[Priority];
    SetPriorityClass(GameHandle, StartPriority);

    if (!EventHook)
        EventHook = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, nullptr, WinEventProc, 0, 0, WINEVENT_OUTOFCONTEXT); // create event hook for window change detection

    return true;
}

bool Unmanaged::IsGameRunning()
{
    DWORD ExitCode = 0;
    GetExitCodeProcess(GameHandle, &ExitCode);
    return ExitCode == STILL_ACTIVE;
}

bool Unmanaged::GetModule(DWORD pid, std::string ModuleName, PMODULEENTRY32 pEntry)
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

DWORD Unmanaged::GetPID(std::string ProcessName)
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

uintptr_t Unmanaged::PatternScan(PVOID module, LPCSTR signature)
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

std::string Unmanaged::GetGamePath()
{
    DWORD pid = 0;
    if (!(pid = GetPID("YuanShen.exe")) && !(pid = GetPID("GenshinImpact.exe")))
        return {};

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | SYNCHRONIZE | PROCESS_TERMINATE, FALSE, pid);

    char szPath[MAX_PATH]{};
    DWORD length = sizeof(szPath);
    QueryFullProcessImageNameA(hProcess, 0, szPath, &length);

    TerminateProcess(hProcess, 0);
    return szPath;
}

std::string Unmanaged::GetLastErrorAsString(DWORD code)
{
    LPSTR buf = nullptr;
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buf, 0, NULL);
    std::string ret = buf;
    LocalFree(buf);
    return ret;
}

bool Unmanaged::SetupData()
{
    MODULEENTRY32 UnityPlayer{};
    if (!GetModule(GamePID, "UnityPlayer.dll", &UnityPlayer))
        return false;

    LPVOID mem = VirtualAlloc(nullptr, UnityPlayer.modBaseSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!mem)
        return ShowError("VirtualAlloc", GetLastError());

    if (!ReadProcessMemory(GameHandle, UnityPlayer.modBaseAddr, mem, UnityPlayer.modBaseSize, nullptr))
        return ShowError("ReadProcessMemory", GetLastError()) && VirtualFreeEx(GameHandle, mem, 0, MEM_RELEASE) == -1;

    /*
         7F 0F              jg   0x11
         8B 05 ? ? ? ?      mov eax, dword ptr[rip+?]
    */
    uintptr_t address = PatternScan(mem, "7F 0F 8B 05 ? ? ? ?");
    if (!address)
        return MessageBoxA(nullptr, "outdated fps pattern", "Error", MB_OK | MB_ICONERROR) == -1 && VirtualFreeEx(GameHandle, mem, 0, MEM_RELEASE) == -1; // lazy returns, should always evaluate to false

    {
        uintptr_t rip = address + 2;
        int32_t rel = *(int32_t*)(rip + 2);
        pFPSValue = rip + rel + 6;
        pFPSValue -= (uintptr_t)mem;
        pFPSValue = (uintptr_t)UnityPlayer.modBaseAddr + pFPSValue;
    }

    address = PatternScan(mem, "E8 ? ? ? ? 8B E8 49 8B 1E");
    if (address)
    {
        uintptr_t ppvsync = 0;
        uintptr_t rip = address;
        int32_t rel = *(int32_t*)(rip + 1);
        rip = rip + rel + 5;
        uint64_t rax = *(uint32_t*)(rip + 3);
        ppvsync = rip + rax + 7;
        ppvsync -= (uintptr_t)mem;
        ppvsync = (uintptr_t)UnityPlayer.modBaseAddr + ppvsync;

        uintptr_t buffer = 0;
        while (!buffer)
        {
            ReadProcessMemory(GameHandle, (LPCVOID)ppvsync, &buffer, sizeof(buffer), nullptr);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        rip += 7;
        pVSyncValue = *(uint32_t*)(rip + 2);
        pVSyncValue = buffer + pVSyncValue;
    }

    VirtualFreeEx(GameHandle, mem, 0, MEM_RELEASE);

    return true;
}

void Unmanaged::ApplyFPS(int fps, bool powerSave)
{
    UsePowerSave = powerSave; // idc lol

    if (!pFPSValue || (InBackground && UsePowerSave))
        return;

    ApplyFPSImpl(fps);
}

void Unmanaged::ApplyFPSImpl(int fps)
{
    int current = 0;
    ReadProcessMemory(GameHandle, (LPCVOID)pFPSValue, &current, sizeof(current), nullptr);

    if (current < 0)
        return;

    if (current == fps)
        return;

    fps = (std::max)(1, fps);
    WriteProcessMemory(GameHandle, (LPVOID)pFPSValue, &fps, sizeof(fps), nullptr);
}

void Unmanaged::ApplyVSync(bool disable)
{
    if (!pVSyncValue)
        return;

    int vsync = !disable;
    WriteProcessMemory(GameHandle, (LPVOID)pVSyncValue, &vsync, sizeof(vsync), nullptr);
}

void Unmanaged::InjectDLLs(std::vector<std::string> paths)
{
    if (!paths.size())
        return;

    LPVOID mem = VirtualAllocEx(GameHandle, nullptr, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!mem)
    {
        ShowError("VirtualAllocEx", GetLastError());
        return;
    }

    BYTE dummyBuffer[0x1000]{};
    auto pLoadLibraryA = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

    // reuse the same buffer for injection
    for (auto it : paths)
    {
        WriteProcessMemory(GameHandle, mem, it.data(), it.size(), nullptr);
        HANDLE hThread = CreateRemoteThread(GameHandle, nullptr, 0, (LPTHREAD_START_ROUTINE)pLoadLibraryA, mem, 0, nullptr);
        if (!hThread)
        {
            ShowError("CreateRemoteThread", GetLastError());
            break;
        }

        WaitForSingleObject(hThread, -1);
        CloseHandle(hThread);
        WriteProcessMemory(GameHandle, mem, dummyBuffer, 0x1000, nullptr);
    }

    VirtualFreeEx(GameHandle, mem, 0, MEM_RELEASE);
}

bool Unmanaged::ShowError(std::string apiName, DWORD code)
{
    auto errorString = GetLastErrorAsString(code);
    std::string message = apiName + " failed with code: " + std::to_string(code) + "\n\n";
    message += errorString;
    MessageBoxA(nullptr, message.c_str(), "Error", MB_OK | MB_ICONERROR);
    return false;
}

bool Unmanaged::VerifyDLL(PVOID module)
{
    if (!module)
        return false;

    uintptr_t base = reinterpret_cast<uintptr_t>(module);

    auto dosHeader = (PIMAGE_DOS_HEADER)base;
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
        return false;

    auto ntHeader = (PIMAGE_NT_HEADERS)(base + dosHeader->e_lfanew);
    if (ntHeader->Signature != IMAGE_NT_SIGNATURE)
        return false;

    return ntHeader->FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64;
}

#pragma managed
