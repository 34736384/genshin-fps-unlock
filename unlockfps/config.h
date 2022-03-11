#pragma once

#include <Windows.h>
#include <string>
#include <vector>

bool WriteConfig(std::string GamePath, int fpsIndex, int fpsOffset, int VSyncEnable);
void LoadConfig();
