#pragma once
//#include <WinUser.h>

#define VERSION "v1.4.3"
 
#define KEY_COMBO VK_HOME
#define KEY_TOGGLE VK_END
#define KEY_INCREASE VK_UP
#define KEY_INCREASE_SMALL VK_RIGHT
#define KEY_DECREASE VK_DOWN
#define KEY_DECREASE_SMALL VK_LEFT

#define INI_SECTION_SETTING "Setting"
#define INI_KEY_PATH "Path"
#define INI_KEY_FPS "Fps"
#define INI_KEY_FPS_CAPS "Fps Caps"
#define INI_KEY_D_POWER_SAVING_ENABLED "Power Saving Enabled"
#define INI_KEY_D_POWER_SAVING_FPS "Power Saving Fps"
#define INI_KEY_DELAY "Power Saving Delay"
#define INI_KEY_VSYNC "VSYNC"

#define INI_SECTION_KEY_BINDING "Key Binding"
#define INI_KEY_COMBO "Combo"
#define INI_KEY_TOGGLE "Toggle"
#define INI_KEY_INCREASE "Increase"
#define INI_KEY_INCREASE_SMALL "Increase Small"
#define INI_KEY_DECREASE "Decrease"
#define INI_KEY_DECREASE_SMALL "Decrease Small"

#define VKEY_MAX 256
#define VKEY_LEN 64

const auto MIN_FPS = 1;

const auto CONFIG_FILE = "fps_config.ini";

// Preset. configurable in the ini file mentioned above
const int BIG_STEP = 12;
const int SMALL_STEP = 1;
const int D_TARGET_FPS = 120;
const bool D_POWER_SAVING_ENABLED = true;
const int D_POWER_SAVING_FPS = 3;
// Useful for ADHD players who switch between windows all the time
const int D_POWER_SAVING_DELAY = 10;
const char D_FPS_CAPS[] = "3 10 30 60 75 95 120 144";
const bool D_VSYNC = false;
