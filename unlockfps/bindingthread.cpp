#include "bindingthread.h"

#include <iterator>
#include <algorithm>
#include <cmath>
#include <thread>

#include "config.h"
#include "definitions.h"
#include "state.h"

// index of the largest number that not larger than the value.
int closest(const int& fps) { 
	const auto &caps = Configurator::getFpsCaps();
	const auto it = std::upper_bound(caps.begin(), caps.end(), fps);
	return max(it - caps.begin() - 1, 0);
};

int Decrease(const bool& bigStep) {
	const auto arrlen = Configurator::getFpsCaps().size();
	const auto fpsIndex = closest(Configurator::getFps());
	const auto& caps = Configurator::getFpsCaps();
	const auto& fps = Configurator::getFps();
	auto newFps = 0;
	if (bigStep)
	{
		if (caps[arrlen - 1] + BIG_STEP < fps)
			newFps = Configurator::decreaseFps(BIG_STEP);
		else
			if (std::find(caps.begin(), caps.end(), fps) == caps.end())
				newFps = Configurator::setFps(caps[fpsIndex]);
			else
				newFps = Configurator::setFps(caps[max(fpsIndex - 1, 0)]);
	}
	else
		newFps = Configurator::decreaseFps(SMALL_STEP);
	return newFps;
}

int Increase(const bool& bigStep) {
	const auto arrlen = Configurator::getFpsCaps().size();
	const auto fpsIndex = closest(Configurator::getFps());
	const auto& caps = Configurator::getFpsCaps();
	const auto& fps = Configurator::getFps();
	auto newFps = 0;
	if (bigStep)
		if (caps[arrlen - 1] <= fps)
			// equal or greater than greatest value in the vector
			newFps = Configurator::increaseFps(BIG_STEP);
		else
			newFps = Configurator::setFps(Configurator::getFpsCaps()[fpsIndex + 1]);
	else
		newFps = Configurator::increaseFps(SMALL_STEP);
	return newFps;
}

DWORD __stdcall Thread1(LPVOID p)
{
	auto prev = Configurator::getFps();

	while (!State::bStop)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		bool comboPressed = GetAsyncKeyState(KEY_COMBO) & 0x8000;

		if (comboPressed && GetAsyncKeyState(KEY_DECREASE) & 1) 
			Decrease(true);
		if (comboPressed && GetAsyncKeyState(KEY_DECREASE_SMALL) & 1) 
			Decrease(false);
		if (comboPressed && GetAsyncKeyState(KEY_INCREASE) & 1) 
			Increase(true);
		if (comboPressed && GetAsyncKeyState(KEY_INCREASE_SMALL) & 1) 
			Increase(false);

		// toggle
		if (comboPressed && GetAsyncKeyState(KEY_TOGGLE) & 1)
			State::bEnabled = !State::bEnabled;

		const auto fps = Configurator::getFps();

		if (prev != fps)
		{
			Configurator::WriteConfig();
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
