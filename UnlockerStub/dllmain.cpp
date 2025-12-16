// ReSharper disable CppClangTidyMiscUseInternalLinkage
#include <Windows.h>
#include <DbgHelp.h>
#include <ranges>
#include <algorithm>
#include "Utils.h"
#include "Zydis.h"

#pragma comment(lib, "dbghelp.lib")
#pragma comment(lib, "ntdll.lib")
EXTERN_C NTSTATUS __stdcall LdrAddRefDll(ULONG Flags, PVOID BaseAddress);

namespace
{
	HMODULE ModuleBase = nullptr;
	int32_t* pFramerate = nullptr;
	HWND GameWindow = nullptr;

	uint8_t* HookHandle = nullptr;
	uint8_t* HookTarget = nullptr;
	uint64_t OriginalBytes = 0;
	uint8_t* ChangeMobileUI = nullptr;

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
		bool UseMobileUI;
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

	if (mbi.Protect != PAGE_READWRITE &&
		mbi.Protect != PAGE_WRITECOPY &&
		mbi.Protect != PAGE_EXECUTE_READWRITE && 
		mbi.Protect != PAGE_EXECUTE_WRITECOPY)
	{
		wchar_t msg[256]{};
		swprintf_s(msg, L"invalid address\naddress %p is not writable\npage protection: 0x%X", pFramerate, mbi.Protect);

		Utils::ShowError(msg);
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

bool UninstallHook()
{
	DWORD oldProtect = 0;
	VirtualProtect(HookTarget, 8, PAGE_EXECUTE_READWRITE, &oldProtect);
	*reinterpret_cast<uint64_t*>(HookTarget) = OriginalBytes;
	VirtualProtect(HookTarget, 8, oldProtect, &oldProtect);
	FlushInstructionCache((HANDLE)-1, HookTarget, 8);
	return true;
}

void HookProc(void* rcx)
{
	ZydisDecoder decoder{};
	ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

	ZydisDecodedInstruction instruction{};
	ZydisDecoderContext context{};
	ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT_VISIBLE]{};

	uint32_t offset = 0;
	int32_t processed = 0;

	ZydisRegister thisReg = ZYDIS_REGISTER_RCX;
	for (uint8_t* rip = ChangeMobileUI; processed < 0x200; rip += instruction.length, processed += instruction.length)
	{
		if (uint16_t code = *reinterpret_cast<uint16_t*>(rip); code == 0x90CC || code == 0xCCCC)
			break;

		auto status = ZydisDecoderDecodeInstruction(&decoder, &context, rip, ZYDIS_MAX_INSTRUCTION_LENGTH, &instruction);
		if (!ZYAN_SUCCESS(status)) {
			instruction.length = 1;
			continue;
		}

		status = ZydisDecoderDecodeOperands(&decoder, &context, &instruction, operands, instruction.operand_count_visible);
		if (!ZYAN_SUCCESS(status)) {
			continue;
		}

		if (instruction.operand_count != 2) {
			continue;
		}

		if (operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
			operands[1].type == ZYDIS_OPERAND_TYPE_REGISTER &&
			operands[1].reg.value == thisReg) {
			thisReg = operands[0].reg.value;
		}
		else if (operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY && operands[1].mem.base == thisReg && operands[1].mem.disp.has_displacement) {
			offset = static_cast<int32_t>(operands[1].mem.disp.value);
			break;
		}
		
	}

	if (offset > 0)
	{
		std::vector<uint8_t> buffer(0x1000, 0);
		*reinterpret_cast<uint8_t**>(buffer.data() + offset) = buffer.data();

		using ChangeMobileUIFn = void(__fastcall*)(uint8_t*);
		reinterpret_cast<ChangeMobileUIFn>(ChangeMobileUI)(buffer.data());
	}

	UninstallHook();
	reinterpret_cast<decltype(&HookProc)>(HookHandle)(rcx);
	VirtualFree(HookHandle, 0, MEM_RELEASE);
}

bool InstallHook()
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

	auto results = Utils::PatternScanAll(il2cppSection, "56 48 83 EC ? 48 89 CE 80 3D ? ? ? ? ? 75 ? E8 ? ? ? ? 3B 46 ? 7E");
	if (results.empty()) {
		Utils::ShowError(L"outdated pattern");
		return false;
	}

	uint8_t* target = HookTarget = results.front();

	results = Utils::PatternScanAll(il2cppSection, "E8 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 90 ? ? ? ? 48 85 D2 0F 84 ? ? ? ? 80 3D ? ? ? ? ? 0F 85 ? ? ? ? C6 42 ? ? 48 8B 90");
	if (results.empty())
	{
		Utils::ShowError(L"outdated pattern");
		return false;
	}

	ChangeMobileUI = results.front() + *reinterpret_cast<int32_t*>(results.front() + 1) + 5;

	HookHandle = Utils::AllocatePage(target, 0x1000, PAGE_EXECUTE_READWRITE);
	if (!HookHandle)
	{
		Utils::ShowWin32Error(L"VirtualAlloc");
		return false;
	}

	ZydisDecoder decoder{};
	ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

	ZydisDecodedInstruction instruction{};
	ZydisDecoderContext context{};

	int32_t offset = 0;
	for (uint8_t* rip = target; offset < 5; rip += instruction.length)
	{
		auto status = ZydisDecoderDecodeInstruction(&decoder, &context, rip, ZYDIS_MAX_INSTRUCTION_LENGTH, &instruction);
		if (!ZYAN_SUCCESS(status))
		{
			Utils::ShowError(L"Failed to decode instruction for hook");
			return false;
		}

		const auto src = rip;
		const auto dst = HookHandle + (rip - target);
		std::memcpy(dst, src, instruction.length);

		offset += instruction.length;
	}

	uint8_t* jumpBack = target + offset;
	uint8_t* jumpBackProc = HookHandle + offset;
	int32_t jumpBackDisp = static_cast<int32_t>(jumpBack - (jumpBackProc + 5));
	jumpBackProc[0] = 0xE9;
	*reinterpret_cast<int32_t*>(&jumpBackProc[1]) = jumpBackDisp;
	offset += 5;

	uint8_t* trampoline = HookHandle + offset;
	trampoline[0] = 0xFF;
	trampoline[1] = 0x25;
	*reinterpret_cast<int32_t*>(&trampoline[2]) = 0;
	*reinterpret_cast<uint64_t*>(trampoline + 6) = reinterpret_cast<uint64_t>(&HookProc);

	DWORD oldProtect = 0;
	VirtualProtect(target, 8, PAGE_EXECUTE_READWRITE, &oldProtect);
	int32_t trampolineDisp = static_cast<int32_t>(trampoline - (target + 5));
	uint8_t jumpCode[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	*reinterpret_cast<uint64_t*>(&jumpCode[0]) = OriginalBytes = *reinterpret_cast<uint64_t*>(target);
	jumpCode[0] = 0xE9;
	*reinterpret_cast<int32_t*>(&jumpCode[1]) = trampolineDisp;
	*reinterpret_cast<uint64_t*>(target) = *reinterpret_cast<uint64_t*>(jumpCode);
	VirtualProtect(target, 8, oldProtect, &oldProtect);

	FlushInstructionCache((HANDLE)-1, target, 5);
	return true;
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

	if (ipcData->UseMobileUI)
	{
		if (!InstallHook())
		{
			Utils::ShowError(L"Failed to set mobile UI");
			return 0;
		}
	}

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
