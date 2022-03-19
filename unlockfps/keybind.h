#pragma once

#include <Windows.h>

#include <string>
#include <cstring>
#include <regex>
#include <algorithm>
#include <cstdint>

#include "definitions.h"

class KeyBind
{
private:
	KeyBind() = delete;

private:
	static const char VK_LIST[VKEY_MAX][VKEY_LEN];

public:
	static int GetValue(const std::string& str);
	static std::string GetVKString(const int& value);
};

