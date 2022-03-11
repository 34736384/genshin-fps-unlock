#include "bindingthread.h"

#include <iterator>
#include <algorithm>
#include <cmath>
#include <thread>
#include "config.h"
#include "definitions.h"

#include "variables.h"

int closest(const int& fps) {
	const auto begin = std::begin(DEFAULT_FPS_STEPS);
	const auto end = std::end(DEFAULT_FPS_STEPS);
	auto it = std::lower_bound(begin, end, fps);
	if (it == begin)
		return 0;
	if (it == end)
		return end - begin - 1;

	it = (std::abs(*(it - 1) - fps) < std::abs(*it - fps)) ? it - 1 : it;
	return it - begin;
};

void Decrease(const bool& bigStep, int& fpsIndex, int& fpsOffset) {
	const static auto arrlen = std::end(DEFAULT_FPS_STEPS) - std::begin(DEFAULT_FPS_STEPS);
	if (bigStep) {
		if (fpsOffset <= 0) 
			fpsIndex = max(0, fpsIndex - 1);
		if (fpsIndex != arrlen - 1 || fpsOffset < BIG_STEP) 
			fpsOffset = 0;
		else
			fpsOffset -= BIG_STEP;
	}
	else {
		const auto targetFps = max(DEFAULT_FPS_STEPS[fpsIndex] + fpsOffset - SMALL_STEP, 1);
		fpsIndex = closest(targetFps);
		fpsOffset = targetFps - DEFAULT_FPS_STEPS[fpsIndex];
	}
}

void Increase(const bool& bigStep, int& fpsIndex, int& fpsOffset) {
	const static auto arrlen = std::end(DEFAULT_FPS_STEPS) - std::begin(DEFAULT_FPS_STEPS);
	if (bigStep) {
		if (fpsIndex < arrlen - 1) {
			if (fpsOffset >= 0) 
				fpsIndex += 1;
			fpsOffset = 0;
		}
		else if (fpsOffset < 0) 
			fpsOffset = 0;
		else
			fpsOffset += BIG_STEP;
	}
	else {
		const auto targetFps = DEFAULT_FPS_STEPS[fpsIndex] + fpsOffset + SMALL_STEP;
		fpsIndex = closest(targetFps);
		fpsOffset = targetFps - DEFAULT_FPS_STEPS[fpsIndex];
	}
}

DWORD __stdcall Thread1(LPVOID p)
{
	if (!p)
		return 0;

	int* pTargetFPS = (int*)p;
	int prev = *pTargetFPS;
	auto fpsIndex = closest(*pTargetFPS);
	auto fpsOffset = *pTargetFPS - DEFAULT_FPS_STEPS[fpsIndex];

	while (!bStop)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		bool comboPressed = GetAsyncKeyState(KEY_COMBO) & 0x8000;

		if (comboPressed && GetAsyncKeyState(KEY_DECREASE) & 1) 
			Decrease(true, fpsIndex, fpsOffset);
		if (comboPressed && GetAsyncKeyState(KEY_DECREASE_SMALL) & 1) 
			Decrease(false, fpsIndex, fpsOffset);
		if (comboPressed && GetAsyncKeyState(KEY_INCREASE) & 1) 
			Increase(true, fpsIndex, fpsOffset);
		if (comboPressed && GetAsyncKeyState(KEY_INCREASE_SMALL) & 1) 
			Increase(false, fpsIndex, fpsOffset);

		// toggle
		if (comboPressed && GetAsyncKeyState(KEY_TOGGLE) & 1)
			Enabled = !Enabled;

		auto fps = DEFAULT_FPS_STEPS[fpsIndex] + fpsOffset;

		if (prev != fps)
			WriteConfig(GamePath, fpsIndex, fpsOffset, VSyncEnable);

		prev = fps;

		if (Enabled)
			if (LowPower)
				printf("\rPower Saving     ");
			else
				printf("\rTarget FPS: %3d  ", fps);
		else
			printf("\rDisabled: %3dfps ", DefaultFPS);

		*pTargetFPS = fps;
	}

	return 0;
}
