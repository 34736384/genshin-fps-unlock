#pragma once

#include <Windows.h>

#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <algorithm>

#include "inireader.h"

#include "definitions.h"

class Configurator 
{
private:
	static std::string gamePath;

	static int fps;
	static std::vector<int> fpsCaps;

	static int powerSavingFps;

	static bool vsync;

private:
	Configurator() = delete;

	static DWORD GetPID(std::string ProcessName);

	static void createConfig(const INIReader &reader);

	static const std::string fpsCaps2str()
	{
		std::ostringstream oss;
		std::for_each(fpsCaps.begin(), fpsCaps.end(), 
			[&](const int& value) { oss << value << ' ';  });
		return oss.str();
	};
	static const void str2fpsCaps(const std::string &str)
	{
		int i;
		fpsCaps.clear();
		std::istringstream iss(str);
		while (iss >> i)
		{
			fpsCaps.push_back(i);
			if (iss.eof())
				break;
		}
	}

	static void LoadConfig();

public:
	static bool WriteConfig();

	// no setter for this value
	static std::string getGamePath() 
	{
		return gamePath;
	};

	static int increaseFps(const int &gain)
	{
		return (Configurator::fps += gain);
	}
	static int decreaseFps(const int& loss)
	{
		const auto value = Configurator::fps - loss;
		return (Configurator::fps = max(value, MIN_FPS));
	}
	static int setFps(const int& fps)
	{
		return (Configurator::fps = max(fps, MIN_FPS));
	}
	static int getFps() 
	{
		return fps;
	};

	// no setter for this value
	static std::vector<int> &getFpsCaps()
	{
		return fpsCaps;
	}
	static std::string getFpsCapsStr()
	{
		return fpsCaps2str();
	}

	// no setter for this value
	static int getPowerSavingFps()
	{
		return powerSavingFps;
	};

	// no setter for this value
	static bool getVSync()
	{
		return vsync;
	}

private: // initialize
	class Initializer
	{
	public:
		Initializer() 
		{
			// default values. no default value for game path
			Configurator::str2fpsCaps(std::string(DEFAULT_FPS_CAPS));
			Configurator::fps = TARGET_FPS;
			Configurator::powerSavingFps = POWER_SAVING_FPS;
			Configurator::vsync = DEFAULT_VSYNC;

			// load from the config file. or create if unavailable/invalid.
			Configurator::LoadConfig();
		}
	};
	friend class Initializer;
	static Initializer initializer;
};
