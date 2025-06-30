#include <windows.h>

#pragma comment(lib, "ntdll.lib")
EXTERN_C NTSTATUS __stdcall LdrAddRefDll(ULONG Flags, PVOID BaseAddress);

bool bExit = false;
struct IPCData* pIPCData = nullptr;

enum class IPCStatus : int
{
	Error = -1,
	None = 0,
	HostAwaiting = 1,
	ClientReady = 2,
	ClientExit = 3,
	HostExit = 4
};

struct __declspec(align(8)) IPCData
{
	ULONG64 Address;
	int Value;
	IPCStatus Status;
};

template<typename T, typename Func>
class MemoryGuard
{
	T pResource;
	Func pFunc;
public:
	MemoryGuard(T pAddress, Func pFunc) : pResource(pAddress), pFunc(pFunc) {}
	~MemoryGuard() { if (pResource) pFunc(pResource); }
	operator T() const { return pResource; }
	T Get() const { return pResource; }
	operator bool() const { return pResource != nullptr && pResource != INVALID_HANDLE_VALUE; }
};

using HandleGuard = MemoryGuard<HANDLE, decltype(&CloseHandle)>;
using MappedMemoryGuard = MemoryGuard<LPVOID, decltype(&UnmapViewOfFile)>;

template<typename T>
T Clamp(T val, T min, T max)
{
	return val < min ? min : val > max ? max : val;
}

BOOL __declspec(noinline) OnWinError(const char* szFunction, DWORD dwError)
{
	char szMessage[256];
	wsprintfA(szMessage, "%s failed with error %d", szFunction, dwError);
	MessageBoxA(nullptr, szMessage, "Error", MB_ICONERROR);

	if (pIPCData)
		pIPCData->Status = IPCStatus::Error;

	return FALSE;
}

DWORD __stdcall ThreadProc(LPVOID lpParameter)
{
	const auto hModule = static_cast<HMODULE>(lpParameter);
	LdrAddRefDll(1, hModule);

	constexpr auto szGuid = "2DE95FDC-6AB7-4593-BFE6-760DD4AB422B";

	const auto hMapFile = HandleGuard(OpenFileMappingA(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, szGuid), CloseHandle);
	if (!hMapFile)
		return OnWinError("OpenFileMapping", GetLastError());

	const auto lpView = MappedMemoryGuard(MapViewOfFile(hMapFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0), UnmapViewOfFile);
	if (!lpView)
		return OnWinError("MapViewOfFile", GetLastError());

	pIPCData = static_cast<IPCData*>(lpView.Get());

	// the address shouldn't change, so we make a copy to make sure it's not changed by the host
	const auto pFpsValue = reinterpret_cast<int*>(pIPCData->Address);

	// check if the address is valid
	MEMORY_BASIC_INFORMATION mbi{};
	if (!VirtualQuery(pFpsValue, &mbi, sizeof(mbi)))
		return OnWinError("VirtualQuery", GetLastError());

	if (mbi.Protect != PAGE_READWRITE)
		return OnWinError("VirtualQuery", ERROR_INVALID_ADDRESS);

	pIPCData->Status = IPCStatus::ClientReady;

	while (pIPCData->Status != IPCStatus::HostExit)
	{
		const auto targetValue = Clamp(pIPCData->Value, 1, 1000);
		*pFpsValue = targetValue;

		Sleep(62);
	}

	pIPCData->Status = IPCStatus::ClientExit;
	return 0;
}

BOOL __stdcall DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpReserved)
{
	if (hInstance)
		DisableThreadLibraryCalls(hInstance);

	if (!GetModuleHandleA("mhypbase.dll"))
		return TRUE;

	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		const auto hThread = CreateThread(nullptr, 0, ThreadProc, hInstance, 0, nullptr);
		if (!hThread)
			return OnWinError("CreateThread", GetLastError());

		CloseHandle(hThread);
	}

	return TRUE;
}

EXTERN_C __declspec(dllexport) LRESULT __stdcall WndProc(int code, WPARAM wParam, LPARAM lParam)
{
	return CallNextHookEx(nullptr, code, wParam, lParam);
}
