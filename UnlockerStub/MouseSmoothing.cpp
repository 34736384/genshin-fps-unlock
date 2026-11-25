#include "MouseSmoothing.h"
#include "Utils.h"
#include <cstring>

namespace
{
	enum class State { Uninitialized, Ready, Failed };
	State InitState = State::Uninitialized;

	uint8_t* Branch = nullptr; // `0F 84 rel32` (je), patched to `90 E9 rel32` (nop; jmp)
	bool Patched = false;

	bool FindBranch()
	{
		const auto il2cpp = Utils::GetIl2CppSection();
		if (il2cpp.empty())
			return false;

		//   mov eax,r8d; mov r8,rdx; mov rsi,rcx; ...; test r9b,r9b; je; (raw *= sensitivity) ...
		//   mov [rsi+RAW],r8; test al,al; je <unsmoothed>; movss xmm10,[rsi+SMOOTHED] ...
		const auto results = Utils::PatternScanAll(il2cpp,
			"44 89 C0 49 89 D0 48 89 CE 80 3D ? ? ? ? 00 0F 85 ? ? ? ? 66 41 0F 6E F0 45 84 C9 74 ? "
			"48 8B 0D ? ? ? ? 48 8B 89 ? ? ? ? 48 85 C9 0F 84 ? ? ? ? 49 C1 E8 20 66 41 0F 6E C0 "
			"F3 0F 59 B1 ? ? ? ? F3 0F 59 81 ? ? ? ? 66 41 0F 7E F0 66 0F 7E C1 48 C1 E1 20 49 09 C8 "
			"4C 89 86 ? ? ? ? 84 C0 0F 84 ? ? ? ? F3 44 0F 10 96");
		if (results.size() != 1)
			return false;

		const auto branch = results.front() + 0x69;
		// both opcode bytes must sit in one aligned qword so the swap is a single atomic store
		const auto qword = reinterpret_cast<uintptr_t>(branch) & ~uintptr_t(7);
		if (reinterpret_cast<uintptr_t>(branch) + 1 >= qword + 8 || branch[0] != 0x0F || branch[1] != 0x84)
			return false;

		Branch = branch;
		return true;
	}

	void SetPatched(bool patch)
	{
		const auto qword = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(Branch) & ~uintptr_t(7));
		const size_t at = Branch - qword;

		uint8_t bytes[8];
		std::memcpy(bytes, qword, 8);
		bytes[at] = patch ? 0x90 : 0x0F;
		bytes[at + 1] = patch ? 0xE9 : 0x84;
		uint64_t value;
		std::memcpy(&value, bytes, 8);

		DWORD oldProtect = 0;
		if (!VirtualProtect(qword, 8, PAGE_EXECUTE_READWRITE, &oldProtect))
			return;
		InterlockedExchange64(reinterpret_cast<volatile LONG64*>(qword), static_cast<LONG64>(value));
		VirtualProtect(qword, 8, oldProtect, &oldProtect);
		FlushInstructionCache(GetCurrentProcess(), qword, 8);
		Patched = patch;
	}
}

void MouseSmoothing::Tick(bool disable)
{
	if (InitState == State::Uninitialized)
	{
		if (!disable)
			return; // don't touch anything unless the feature is used

		InitState = FindBranch() ? State::Ready : State::Failed;
		if (InitState == State::Failed)
			Utils::ShowError(L"Disable mouse smoothing: pattern not found, the game version is probably unsupported.\nThe option will be ignored.");
	}

	if (InitState == State::Ready && disable != Patched)
		SetPatched(disable);
}
