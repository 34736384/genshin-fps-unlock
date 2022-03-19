#include "state.h"
#include "definitions.h"
#include "config.h"

bool State::bStop = false;
bool State::bPowerSavingMode = false;
bool State::bEnabled = true;
bool State::bCounting = false;
bool State::bTimeout = false;

void State::CountDown()
{
	static std::chrono::time_point<std::chrono::system_clock> start_time = 
		std::chrono::system_clock::now();
	if (bCounting)
	{
		auto now = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> duration = now - start_time;
		auto durationSec = static_cast<int>((duration.count() + 500) / 1000);
		if (durationSec >= Config::GetPowerSavingDelay()) {
			bCounting = false;
			bTimeout = true;
		}
	}
	else if (!bTimeout)
	{
		start_time = std::chrono::system_clock::now();
		bCounting = true;
	}
}

bool State::GetPowerSavingState(const bool inFocus)
{
	if (inFocus)
	{
		bCounting = false;
		bTimeout = false;
		return false;
	}
	else
		CountDown();
	return bTimeout;
}
