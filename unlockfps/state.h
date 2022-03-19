#pragma once

#include <chrono>

class State 
{
public:
	static bool bStop;
	static bool bPowerSavingMode;
	static bool bEnabled;

public:
	static bool GetPowerSavingState(const bool inFocus);

private:
	State() = delete;
	static void CountDown();

private:
	static bool bCounting;
	static bool bTimeout;
};
