#include "VerticalSensitivity.h"
#include "Utils.h"
#include <cmath>
#include <algorithm>
#include <cstring>

namespace
{
	enum class State { Uninitialized, Ready, Failed };
	State InitState = State::Uninitialized;

	// camera controller: [[[*Types] + HolderOffset] + EntityOffset] + ControllerOffset
	uint8_t** Types = nullptr;
	uint32_t HolderOffset = 0, EntityOffset = 0, ControllerOffset = 0;
	// global config: [[controller + ProfileOffset] + GlobalConfigOffset], ratios at PolarOffset / ElevationOffset
	uint32_t ProfileOffset = 0;
	uint8_t GlobalConfigOffset = 0, PolarOffset = 0, ElevationOffset = 0;
	// input device: [[*DeviceTypes] + DeviceHolderOffset] + DeviceOffset, 3 = controller
	uint8_t** DeviceTypes = nullptr;
	uint32_t DeviceHolderOffset = 0, DeviceOffset = 0;

	uint8_t* Config = nullptr;     // global config we last touched
	float OriginalElevation = 0;
	bool Modified = false;

	template <typename T> T Read(const uint8_t* p) { T v; std::memcpy(&v, p, sizeof(T)); return v; }
	uint8_t* RipTarget(uint8_t* insn, size_t dispOffset, size_t length) { return insn + length + Read<int32_t>(insn + dispOffset); }

	bool FindOffsets()
	{
		const auto il2cpp = Utils::GetIl2CppSection();
		if (il2cpp.empty())
			return false;

		// Static camera input setters on the camera entity class:
		//   push rsi; sub rsp,20h; mov rsi,rcx; cmp byte [..],0; mov rax,[rip+TYPES]; jne; mov rdx,[rax+HOLDER]; test rdx,rdx; je;
		//   cmp byte [..],0; jne; mov rcx,[rdx+ENTITY]; test rcx,rcx; je; mov rdx,rsi; add rsp,20h; pop rsi; jmp <instance method>
		// The instance method then reads the controller: mov rax,[rdi+CONTROLLER]
		const auto setters = Utils::PatternScanAll(il2cpp,
			"56 48 83 EC 20 48 89 CE 80 3D ? ? ? ? 00 48 8B 05 ? ? ? ? 75 ? 48 8B 90 ? ? ? ? 48 85 D2 74 ? "
			"80 3D ? ? ? ? 00 75 ? 48 8B 8A ? ? ? ? 48 85 C9 74 ? 48 89 F2 48 83 C4 20 5E E9");
		int accepted = 0;
		for (const auto p : setters)
		{
			const auto instance = RipTarget(p + 65, 1, 5);
			if (instance < il2cpp.data() || instance + 0x40 > il2cpp.data() + il2cpp.size())
				continue;
			static const uint8_t prologue[] = { 0x56, 0x57, 0x48, 0x83, 0xEC, 0x28, 0x48, 0x89, 0xD6, 0x48, 0x89, 0xCF };
			if (std::memcmp(instance, prologue, sizeof(prologue)) != 0)
				continue; // a different class with the same static shape
			uint32_t controller = 0;
			for (int k = sizeof(prologue); k < 0x40 && !controller; k++)
				if (instance[k] == 0x48 && instance[k + 1] == 0x8B && instance[k + 2] == 0x87)
					controller = Read<uint32_t>(instance + k + 3);
			if (!controller)
				continue;

			const auto types = reinterpret_cast<uint8_t**>(RipTarget(p + 15, 3, 7));
			const auto holder = Read<uint32_t>(p + 27), entity = Read<uint32_t>(p + 48);
			if (accepted == 0)
			{
				Types = types; HolderOffset = holder; EntityOffset = entity; ControllerOffset = controller;
			}
			else if (types != Types || holder != HolderOffset || entity != EntityOffset || controller != ControllerOffset)
				return false; // ambiguous
			accepted++;
		}
		if (accepted == 0)
			return false;

		// Controller's per-axis ratio getters (horizontal first in the config):
		//   mov rax,[rsi+PROFILE]; xorps xmm0,xmm0; test rax,rax; je; mov rax,[rax+GLOBAL]; test rax,rax; je; movss xmm0,[rax+RATIO]
		const auto getters = Utils::PatternScanAll(il2cpp, "48 8B 86 ? ? ? ? 0F 57 C0 48 85 C0 74 ? 48 8B 40 ? 48 85 C0 74 ? F3 0F 10 40 ?");
		if (getters.size() != 2)
			return false;
		const auto a = getters[0], b = getters[1];
		if (Read<uint32_t>(a + 3) != Read<uint32_t>(b + 3) || a[18] != b[18])
			return false;
		ProfileOffset = Read<uint32_t>(a + 3);
		GlobalConfigOffset = a[18];
		PolarOffset = std::min(a[28], b[28]);
		ElevationOffset = std::max(a[28], b[28]);
		if (ElevationOffset != PolarOffset + 4)
			return false;

		// Input device check (used by the camera's inertia code):
		//   cmp byte [..],0; mov rax,[rip+TYPES]; jne; mov rax,[rax+HOLDER]; test rax,rax; je; cmp dword [rax+DEVICE],3
		const auto device = Utils::PatternScanAll(il2cpp,
			"80 3D ? ? ? ? 00 48 8B 05 ? ? ? ? 0F 85 ? ? ? ? 48 8B 80 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? 83 B8 ? ? ? ? 03 "
			"48 8B 47 ? 75 ? 48 85 C0 0F 84 ? ? ? ? F3 0F 10 B8");
		if (!device.empty())
		{
			const auto p = device.front();
			DeviceTypes = reinterpret_cast<uint8_t**>(RipTarget(p + 7, 3, 7));
			DeviceHolderOffset = Read<uint32_t>(p + 23);
			DeviceOffset = Read<uint32_t>(p + 38);
		}
		return true;
	}

	bool IsReadable(const void* p, size_t n, bool write = false)
	{
		MEMORY_BASIC_INFORMATION mbi{};
		if (!p || !VirtualQuery(p, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)))
			return false;
		const DWORD writable = PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;
		if (write && !(mbi.Protect & writable))
			return false;
		return static_cast<const uint8_t*>(p) + n <= static_cast<const uint8_t*>(mbi.BaseAddress) + mbi.RegionSize;
	}

	uint8_t* ReadPtr(const uint8_t* p) { return p && IsReadable(p, 8) ? *reinterpret_cast<uint8_t* const*>(p) : nullptr; }

	uint8_t* ResolveConfig()
	{
		const auto types = ReadPtr(reinterpret_cast<uint8_t*>(Types));
		const auto holder = types ? ReadPtr(types + HolderOffset) : nullptr;
		const auto entity = holder ? ReadPtr(holder + EntityOffset) : nullptr;
		const auto controller = entity ? ReadPtr(entity + ControllerOffset) : nullptr;
		const auto profile = controller ? ReadPtr(controller + ProfileOffset) : nullptr;
		const auto config = profile ? ReadPtr(profile + GlobalConfigOffset) : nullptr;
		return config && IsReadable(config + PolarOffset, 8, true) ? config : nullptr;
	}

	bool IsController()
	{
		if (!DeviceTypes)
			return false;
		const auto types = ReadPtr(reinterpret_cast<uint8_t*>(DeviceTypes));
		const auto holder = types ? ReadPtr(types + DeviceHolderOffset) : nullptr;
		return holder && IsReadable(holder + DeviceOffset, 4) && Read<int32_t>(holder + DeviceOffset) == 3;
	}

	bool Plausible(float v) { return std::isfinite(v) && v > 0.0f && v < 1.0e4f; }
}

void VerticalSensitivity::Tick(bool enable, int percent)
{
	if (InitState == State::Uninitialized)
	{
		if (!enable)
			return; // don't touch anything unless the feature is used

		InitState = FindOffsets() ? State::Ready : State::Failed;
		if (InitState == State::Failed)
			Utils::ShowError(L"Custom vertical sensitivity: pattern not found, the game version is probably unsupported.\nThe option will be ignored.");
	}
	if (InitState != State::Ready)
		return;

	const auto config = ResolveConfig();
	if (!config)
		return; // no camera yet (loading screen etc.)

	auto& elevation = *reinterpret_cast<volatile float*>(config + ElevationOffset);
	const float polar = *reinterpret_cast<volatile float*>(config + PolarOffset);

	if (config != Config)
	{
		// new camera profile: whatever it holds now is the game's value
		Config = config;
		OriginalElevation = elevation;
		Modified = false;
	}
	if (!Plausible(polar) || !Plausible(OriginalElevation))
		return;

	const bool active = enable && !IsController();
	if (active)
	{
		const float target = polar * static_cast<float>(std::clamp(percent, 10, 200)) / 100.0f;
		if (elevation != target)
			elevation = target;
		Modified = true;
	}
	else if (Modified)
	{
		elevation = OriginalElevation;
		Modified = false;
	}
}
