#pragma once

#define VERSION "v1.4.3"

#define KEY_TOGGLE VK_END
#define KEY_INCREASE VK_UP
#define KEY_INCREASE_SMALL VK_RIGHT
#define KEY_DECREASE VK_DOWN
#define KEY_DECREASE_SMALL VK_LEFT
#define KEY_COMBO VK_HOME

#define INI_SECTION_SETTING "Setting"
#define INI_KEY_PATH "Path"
#define INI_KEY_FPS "Fps"
#define INI_KEY_FPS_CAPS "FpsCaps"
#define INI_KEY_POWER_SAVING_FPS "PowerSavingFps"
#define INI_KEY_VSYNC "VSYNC"

const auto MIN_FPS = 1;

const auto CONFIG_FILE = "fps_config.ini";

// configurable in the ini file mentioned above
const int BIG_STEP = 12;
const int SMALL_STEP = 1;
const int TARGET_FPS = 120;
const int POWER_SAVING_FPS = 3;
const char DEFAULT_FPS_CAPS[] = "3 10 30 60 75 95 120 144";
const bool DEFAULT_VSYNC = false;

