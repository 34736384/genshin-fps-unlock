#include "bindingthread.h"

#include <iterator>
#include <algorithm>
#include <cmath>
#include <thread>

#include "config.h"
#include "definitions.h"
#include "state.h"
#include "keybind.h"

// index of the largest number that not larger than the value.
int Closest(const int& fps) 
{
	const auto& caps = Config::GetFpsCaps();
	const auto it = std::upper_bound(caps.begin(), caps.end(), fps);
	return max(it - caps.begin() - 1, 0);
};

int Decrease(const bool& bigStep) 
{
	const auto arrlen = Config::GetFpsCaps().size();
	const auto fpsIndex = Closest(Config::GetFps());
	const auto& caps = Config::GetFpsCaps();
	const auto& fps = Config::GetFps();
	auto newFps = 0;
	if (bigStep)
	{
		if (caps[arrlen - 1] + BIG_STEP < fps)
			newFps = Config::DecreaseFps(BIG_STEP);
		else
			if (std::find(caps.begin(), caps.end(), fps) == caps.end())
				newFps = Config::SetFps(caps[fpsIndex]);
			else
				newFps = Config::SetFps(caps[max(fpsIndex - 1, 0)]);
	}
	else
		newFps = Config::DecreaseFps(SMALL_STEP);
	return newFps;
}

int Increase(const bool& bigStep) 
{
	const auto arrlen = Config::GetFpsCaps().size();
	const auto fpsIndex = Closest(Config::GetFps());
	const auto& caps = Config::GetFpsCaps();
	const auto& fps = Config::GetFps();
	auto newFps = 0;
	if (bigStep)
		if (caps[arrlen - 1] <= fps)
			// equal or greater than greatest value in the vector
			newFps = Config::IncreaseFps(BIG_STEP);
		else
			newFps = Config::SetFps(Config::GetFpsCaps()[fpsIndex + 1]);
	else
		newFps = Config::IncreaseFps(SMALL_STEP);
	return newFps;
}

DWORD __stdcall Thread1(LPVOID p)
{
	auto prev = Config::GetFps();

	const auto ck = Config::GetComboKey();
	const auto tk = Config::GetToggleKey();
	const auto dk = Config::GetDecreaseKey(true);
	const auto sdk = Config::GetDecreaseKey(false);
	const auto ik = Config::GetIncreaseKey(true);
	const auto sik = Config::GetIncreaseKey(false);

	static const auto pressedSinceLastCall = [](const int& vk) {
		return GetAsyncKeyState(vk) & 0x8000;
	};
	static const auto pressedCurrently = [](const int& vk) {
		return GetAsyncKeyState(vk) & 1;
	};

	while (!State::bStop)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		// ignore combo key if not set (i.e. ck == 0)
		bool comboPressed = ck && pressedSinceLastCall(ck);
		if (dk && comboPressed && pressedCurrently(dk))
			Decrease(true);
		if (sdk && comboPressed && pressedCurrently(sdk))
			Decrease(false);
		if (ik && comboPressed && pressedCurrently(ik))
			Increase(true);
		if (sik && comboPressed && pressedCurrently(sik))
			Increase(false);

		// toggle
		if (tk && comboPressed && pressedCurrently(tk))
			State::bEnabled = !State::bEnabled;

		const auto fps = Config::GetFps();

		if (prev != fps)
		{
			Config::WriteConfig();
		}

		prev = fps;

		if (State::bEnabled)
			if (State::bPowerSavingMode)
				printf("\rPower Saving     ");
			else
				printf("\rTarget FPS: %3d  ", fps);
		else
			printf("\rTool Disabled. ");
	}

	return 0;
}
