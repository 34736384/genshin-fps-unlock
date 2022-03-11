#pragma once

#define VERSION "v1.4.3"

#define KEY_TOGGLE VK_END
#define KEY_INCREASE VK_UP
#define KEY_INCREASE_SMALL VK_RIGHT
#define KEY_DECREASE VK_DOWN
#define KEY_DECREASE_SMALL VK_LEFT
#define KEY_COMBO VK_HOME

const int BIG_STEP = 12;
const int SMALL_STEP = 1;

const int TARGET_FPS_INDEX = 6;
const int POWER_SAVING_FPS_INDEX = 0;

const int DEFAULT_FPS_STEPS[] = { 3, 10, 30, 60, 75, 95, 120, 144, };

const auto CONFIG_FILENAME = "fps_config.ini";
