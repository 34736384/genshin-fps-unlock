#pragma once

#include <Windows.h>

#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <algorithm>

#include "inireader.h"

#include "definitions.h"

class Config 
{
	friend DWORD __stdcall Thread1(LPVOID p);
	friend int Closest(const int& fps);
	friend int Decrease(const bool& bigStep);
	friend int Increase(const bool& bigStep);

private:
	static std::string gamePath;

	static int fps;
	static std::vector<int> fpsCaps;

	static bool powerSavingEnabled;
	static int powerSavingFps;
	static int powerSavingDelay;

	static bool vsync;

private:
	static int comboKey;
	static int toggleKey;
	static int increaseKey;
	static int increaseSmallKey;
	static int decreaseKey;
	static int decreaseSmallKey;

private:
	Config() = delete;

	static DWORD GetPID(std::string ProcessName);

	static void CreateConfig(const INIReader& reader);

	static void LoadConfig();

private:
	
	static const void SetFpsCaps(const std::string &str)
	{
		fpsCaps.clear();
		
		int i;
		std::istringstream iss(str);
		while (iss >> i)
		{
			if (i > 0 && std::find(fpsCaps.begin(), fpsCaps.end(), i) == fpsCaps.end())
				fpsCaps.push_back(i);
			if (iss.eof())
				break;
		}
	}
	static const std::vector<int>& GetFpsCaps()
	{
		return fpsCaps;
	}

	static int SetPowerSavingFps(const int& fps)
	{
		return (powerSavingFps = max(fps, MIN_FPS));
	}

	static int SetPowerSavingDelay(const int& sec)
	{
		return (powerSavingDelay = max(sec, 0));
	}

	static int IncreaseFps(const int& gain)
	{
		return (Config::fps += gain);
	}
	static int DecreaseFps(const int& loss)
	{
		const auto value = Config::fps - loss;
		return (Config::fps = max(value, MIN_FPS));
	}



public:
	static bool WriteConfig();

	// no setter for this value
	static std::string GetGamePath() 
	{
		return gamePath;
	};

	static int SetFps(const int& fps)
	{
		return (Config::fps = max(fps, MIN_FPS));
	}
	static int GetFps() 
	{
		return fps;
	};

	static const std::string GetFpsCapsStr()
	{
		std::ostringstream oss;
		std::for_each(fpsCaps.begin(), fpsCaps.end(),
			[&](const int& value) { oss << value << ' ';  });
		return oss.str();
	};

	static bool IsPowerSavingEnabled()
	{
		return powerSavingEnabled;
	}

	static int GetPowerSavingFps()
	{
		return powerSavingFps;
	};

	static int GetPowerSavingDelay()
	{
		return powerSavingDelay;
	}

	// no setter for this value
	static bool GetVSync()
	{
		return vsync;
	}

	static int GetComboKey()
	{
		return comboKey;
	}

	static int GetToggleKey()
	{
		return toggleKey;
	}

	static int GetIncreaseKey(const bool bigStep)
	{
		return bigStep ? increaseKey : increaseSmallKey;
	}

	static int GetDecreaseKey(const bool bigStep)
	{
		return bigStep ? decreaseKey : decreaseSmallKey;
	}

private: // initialize
	class Init
	{
	public:
		Init() 
		{
			// load from the config file. or create if unavailable/invalid.
			Config::LoadConfig();
		}
	};
	friend class Init;
	static Init init;
};
