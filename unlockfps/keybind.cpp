#define ELEMENT(s) #s

#include "keybind.h"

#include <Windows.h>

#include <cstring>
#include <regex>
#include <algorithm>

const char KeyBind::VK_LIST[VKEY_MAX][VKEY_LEN]
{
	"", // 0x00
#ifdef VK_LBUTTON
	ELEMENT(VK_LBUTTON),
#else
	"",
#endif
#ifdef VK_RBUTTON
	ELEMENT(VK_RBUTTON),
#else
	"",
#endif
#ifdef VK_CANCEL
	ELEMENT(VK_CANCEL),
#else
	"",
#endif
#ifdef VK_MBUTTON
	ELEMENT(VK_MBUTTON),
#else
	"",
#endif
#ifdef VK_XBUTTON1
	ELEMENT(VK_XBUTTON1),
#else
	"",
#endif
#ifdef VK_XBUTTON2
	ELEMENT(VK_XBUTTON2),
#else
	"",
#endif
	"", // 0x07
#ifdef VK_BACK
	ELEMENT(VK_BACK),
#else
	"",
#endif
#ifdef VK_TAB
	ELEMENT(VK_TAB),
#else
	"",
#endif
	"", // 0x0A
	"", // 0x0B
#ifdef VK_CLEAR
	ELEMENT(VK_CLEAR),
#else
	"",
#endif
#ifdef VK_RETURN
	ELEMENT(VK_RETURN),
#else
	"",
#endif
	"", // 0x0E
	"", // 0x0F
#ifdef VK_SHIFT
	ELEMENT(VK_SHIFT),
#else
	"",
#endif
#ifdef VK_CONTROL
	ELEMENT(VK_CONTROL),
#else
	"",
#endif
#ifdef VK_MENU
	ELEMENT(VK_MENU),
#else
	"",
#endif
#ifdef VK_PAUSE
	ELEMENT(VK_PAUSE),
#else
	"",
#endif
#ifdef VK_CAPITAL
	ELEMENT(VK_CAPITAL),
#else
	"",
#endif
#ifdef VK_KANA
	ELEMENT(VK_KANA),
#else
	"",
#endif
#ifdef VK_IME_ON
	ELEMENT(VK_IME_ON),
#else
	"",
#endif
#ifdef VK_JUNJA
	ELEMENT(VK_JUNJA),
#else
	"",
#endif
#ifdef VK_FINAL
	ELEMENT(VK_FINAL),
#else
	"",
#endif
#ifdef VK_HANJA
	ELEMENT(VK_HANJA),
#else
	"",
#endif
#ifdef VK_IME_OFF
	ELEMENT(VK_IME_OFF),
#else
	"",
#endif
#ifdef VK_ESCAPE
	ELEMENT(VK_ESCAPE),
#else
	"",
#endif
#ifdef VK_CONVERT
	ELEMENT(VK_CONVERT),
#else
	"",
#endif
#ifdef VK_NONCONVERT
	ELEMENT(VK_NONCONVERT),
#else
	"",
#endif
#ifdef VK_ACCEPT
	ELEMENT(VK_ACCEPT),
#else
	"",
#endif
#ifdef VK_MODECHANGE
	ELEMENT(VK_MODECHANGE),
#else
	"",
#endif
#ifdef VK_SPACE
	ELEMENT(VK_SPACE),
#else
	"",
#endif
#ifdef VK_PRIOR
	ELEMENT(VK_PRIOR),
#else
	"",
#endif
#ifdef VK_NEXT
	ELEMENT(VK_NEXT),
#else
	"",
#endif
#ifdef VK_END
	ELEMENT(VK_END),
#else
	"",
#endif
#ifdef VK_HOME
	ELEMENT(VK_HOME),
#else
	"",
#endif
#ifdef VK_LEFT
	ELEMENT(VK_LEFT),
#else
	"",
#endif
#ifdef VK_UP
	ELEMENT(VK_UP),
#else
	"",
#endif
#ifdef VK_RIGHT
	ELEMENT(VK_RIGHT),
#else
	"",
#endif
#ifdef VK_DOWN
	ELEMENT(VK_DOWN),
#else
	"",
#endif
#ifdef VK_SELECT
	ELEMENT(VK_SELECT),
#else
	"",
#endif
#ifdef VK_PRINT
	ELEMENT(VK_PRINT),
#else
	"",
#endif
#ifdef VK_EXECUTE
	ELEMENT(VK_EXECUTE),
#else
	"",
#endif
#ifdef VK_SNAPSHOT
	ELEMENT(VK_SNAPSHOT),
#else
	"",
#endif
#ifdef VK_INSERT
	ELEMENT(VK_INSERT),
#else
	"",
#endif
#ifdef VK_DELETE
	ELEMENT(VK_DELETE),
#else
	"",
#endif
#ifdef VK_HELP
	ELEMENT(VK_HELP),
#else
	"",
#endif
#ifndef VK_0
#define VK_0 '0'
#endif
	ELEMENT(VK_0),
#ifndef VK_1
#define VK_1 '1'
#endif
	ELEMENT(VK_1),
#ifndef VK_2
#define VK_2 '2'
#endif
	ELEMENT(VK_2),
#ifndef VK_3
#define VK_3 '3'
#endif
	ELEMENT(VK_3),
#ifndef VK_4
#define VK_4 '4'
#endif
	ELEMENT(VK_4),
#ifndef VK_5
#define VK_5 '5'
#endif
	ELEMENT(VK_5),
#ifndef VK_6
#define VK_6 '6'
#endif
	ELEMENT(VK_6),
#ifndef VK_7
#define VK_7 '7'
#endif
	ELEMENT(VK_7),
#ifndef VK_8
#define VK_8 '8'
#endif
	ELEMENT(VK_8),
#ifndef VK_9
#define VK_9 '9'
#endif
	ELEMENT(VK_9),
	"", // 0x3A
	"", // 0x3B
	"", // 0x3C
	"", // 0x3D
	"", // 0x3E
	"", // 0x3F
	"", // 0x40
#ifndef VK_A
#define VK_A 'A'
#endif
	ELEMENT(VK_A),
#ifndef VK_B
#define VK_B 'B'
#endif
	ELEMENT(VK_B),
#ifndef VK_C
#define VK_C 'C'
#endif
	ELEMENT(VK_C),
#ifndef VK_D
#define VK_D 'D'
#endif
	ELEMENT(VK_D),
#ifndef VK_E
#define VK_E 'E'
#endif
	ELEMENT(VK_E),
#ifndef VK_F
#define VK_F 'F'
#endif
	ELEMENT(VK_F),
#ifndef VK_G
#define VK_G 'G'
#endif
	ELEMENT(VK_G),
#ifndef VK_H
#define VK_H 'H'
#endif
	ELEMENT(VK_H),
#ifndef VK_I
#define VK_I 'I'
#endif
	ELEMENT(VK_I),
#ifndef VK_J
#define VK_J 'J'
#endif
	ELEMENT(VK_J),
#ifndef VK_K
#define VK_K 'K'
#endif
	ELEMENT(VK_K),
#ifndef VK_L
#define VK_L 'L'
#endif
	ELEMENT(VK_L),
#ifndef VK_M
#define VK_M 'M'
#endif
	ELEMENT(VK_M),
#ifndef VK_N
#define VK_N 'N'
#endif
	ELEMENT(VK_N),
#ifndef VK_O
#define VK_O 'O'
#endif
	ELEMENT(VK_O),
#ifndef VK_P
#define VK_P 'P'
#endif
	ELEMENT(VK_P),
#ifndef VK_Q
#define VK_Q 'Q'
#endif
	ELEMENT(VK_Q),
#ifndef VK_R
#define VK_R 'R'
#endif
	ELEMENT(VK_R),
#ifndef VK_S
#define VK_S 'S'
#endif
	ELEMENT(VK_S),
#ifndef VK_T
#define VK_T 'T'
#endif
	ELEMENT(VK_T),
#ifndef VK_U
#define VK_U 'U'
#endif
	ELEMENT(VK_U),
#ifndef VK_V
#define VK_V 'V'
#endif
	ELEMENT(VK_V),
#ifndef VK_W
#define VK_W 'W'
#endif
	ELEMENT(VK_W),
#ifndef VK_X
#define VK_X 'X'
#endif
	ELEMENT(VK_X),
#ifndef VK_Y
#define VK_Y 'Y'
#endif
	ELEMENT(VK_Y),
#ifndef VK_Z
#define VK_Z 'Z'
#endif
	ELEMENT(VK_Z),
#ifdef VK_LWIN
	ELEMENT(VK_LWIN),
#else
	"",
#endif
#ifdef VK_RWIN
	ELEMENT(VK_RWIN),
#else
	"",
#endif
#ifdef VK_APPS
	ELEMENT(VK_APPS),
#else
	"",
#endif
	"", // 0x5E
#ifdef VK_SLEEP
	ELEMENT(VK_SLEEP),
#else
	"",
#endif
#ifdef VK_NUMPAD0
	ELEMENT(VK_NUMPAD0),
#else
	"",
#endif
#ifdef VK_NUMPAD1
	ELEMENT(VK_NUMPAD1),
#else
	"",
#endif
#ifdef VK_NUMPAD2
	ELEMENT(VK_NUMPAD2),
#else
	"",
#endif
#ifdef VK_NUMPAD3
	ELEMENT(VK_NUMPAD3),
#else
	"",
#endif
#ifdef VK_NUMPAD4
	ELEMENT(VK_NUMPAD4),
#else
	"",
#endif
#ifdef VK_NUMPAD5
	ELEMENT(VK_NUMPAD5),
#else
	"",
#endif
#ifdef VK_NUMPAD6
	ELEMENT(VK_NUMPAD6),
#else
	"",
#endif
#ifdef VK_NUMPAD7
	ELEMENT(VK_NUMPAD7),
#else
	"",
#endif
#ifdef VK_NUMPAD8
	ELEMENT(VK_NUMPAD8),
#else
	"",
#endif
#ifdef VK_NUMPAD9
	ELEMENT(VK_NUMPAD9),
#else
	"",
#endif
#ifdef VK_MULTIPLY
	ELEMENT(VK_MULTIPLY),
#else
	"",
#endif
#ifdef VK_ADD
	ELEMENT(VK_ADD),
#else
	"",
#endif
#ifdef VK_SEPARATOR
	ELEMENT(VK_SEPARATOR),
#else
	"",
#endif
#ifdef VK_SUBTRACT
	ELEMENT(VK_SUBTRACT),
#else
	"",
#endif
#ifdef VK_DECIMAL
	ELEMENT(VK_DECIMAL),
#else
	"",
#endif
#ifdef VK_DIVIDE
	ELEMENT(VK_DIVIDE),
#else
	"",
#endif
#ifdef VK_F1
	ELEMENT(VK_F1),
#else
	"",
#endif
#ifdef VK_F2
	ELEMENT(VK_F2),
#else
	"",
#endif
#ifdef VK_F3
	ELEMENT(VK_F3),
#else
	"",
#endif
#ifdef VK_F4
	ELEMENT(VK_F4),
#else
	"",
#endif
#ifdef VK_F5
	ELEMENT(VK_F5),
#else
	"",
#endif
#ifdef VK_F6
	ELEMENT(VK_F6),
#else
	"",
#endif
#ifdef VK_F7
	ELEMENT(VK_F7),
#else
	"",
#endif
#ifdef VK_F8
	ELEMENT(VK_F8),
#else
	"",
#endif
#ifdef VK_F9
	ELEMENT(VK_F9),
#else
	"",
#endif
#ifdef VK_F10
	ELEMENT(VK_F10),
#else
	"",
#endif
#ifdef VK_F11
	ELEMENT(VK_F11),
#else
	"",
#endif
#ifdef VK_F12
	ELEMENT(VK_F12),
#else
	"",
#endif
#ifdef VK_F13
	ELEMENT(VK_F13),
#else
	"",
#endif
#ifdef VK_F14
	ELEMENT(VK_F14),
#else
	"",
#endif
#ifdef VK_F15
	ELEMENT(VK_F15),
#else
	"",
#endif
#ifdef VK_F16
	ELEMENT(VK_F16),
#else
	"",
#endif
#ifdef VK_F17
	ELEMENT(VK_F17),
#else
	"",
#endif
#ifdef VK_F18
	ELEMENT(VK_F18),
#else
	"",
#endif
#ifdef VK_F19
	ELEMENT(VK_F19),
#else
	"",
#endif
#ifdef VK_F20
	ELEMENT(VK_F20),
#else
	"",
#endif
#ifdef VK_F21
	ELEMENT(VK_F21),
#else
	"",
#endif
#ifdef VK_F22
	ELEMENT(VK_F22),
#else
	"",
#endif
#ifdef VK_F23
	ELEMENT(VK_F23),
#else
	"",
#endif
#ifdef VK_F24
	ELEMENT(VK_F24),
#else
	"",
#endif
#ifdef VK_NAVIGATION_VIEW
	ELEMENT(VK_NAVIGATION_VIEW),
#else
	"",
#endif
#ifdef VK_NAVIGATION_MENU
	ELEMENT(VK_NAVIGATION_MENU),
#else
	"",
#endif
#ifdef VK_NAVIGATION_UP
	ELEMENT(VK_NAVIGATION_UP),
#else
	"",
#endif
#ifdef VK_NAVIGATION_DOWN
	ELEMENT(VK_NAVIGATION_DOWN),
#else
	"",
#endif
#ifdef VK_NAVIGATION_LEFT
	ELEMENT(VK_NAVIGATION_LEFT),
#else
	"",
#endif
#ifdef VK_NAVIGATION_RIGHT
	ELEMENT(VK_NAVIGATION_RIGHT),
#else
	"",
#endif
#ifdef VK_NAVIGATION_ACCEPT
	ELEMENT(VK_NAVIGATION_ACCEPT),
#else
	"",
#endif
#ifdef VK_NAVIGATION_CANCEL
	ELEMENT(VK_NAVIGATION_CANCEL),
#else
	"",
#endif
#ifdef VK_NUMLOCK
	ELEMENT(VK_NUMLOCK),
#else
	"",
#endif
#ifdef VK_SCROLL
	ELEMENT(VK_SCROLL),
#else
	"",
#endif
#ifdef VK_OEM_NEC_EQUAL
	ELEMENT(VK_OEM_NEC_EQUAL),
#else
	"",
#endif
#ifdef VK_OEM_FJ_MASSHOU
	ELEMENT(VK_OEM_FJ_MASSHOU),
#else
	"",
#endif
#ifdef VK_OEM_FJ_TOUROKU
	ELEMENT(VK_OEM_FJ_TOUROKU),
#else
	"",
#endif
#ifdef VK_OEM_FJ_LOYA
	ELEMENT(VK_OEM_FJ_LOYA),
#else
	"",
#endif
#ifdef VK_OEM_FJ_ROYA
	ELEMENT(VK_OEM_FJ_ROYA),
#else
	"",
#endif
	"", // 0x97
	"", // 0x98
	"", // 0x99
	"", // 0x9A
	"", // 0x9B
	"", // 0x9C
	"", // 0x9D
	"", // 0x9E
	"", // 0x9F
#ifdef VK_LSHIFT
	ELEMENT(VK_LSHIFT),
#else
	"",
#endif
#ifdef VK_RSHIFT
	ELEMENT(VK_RSHIFT),
#else
	"",
#endif
#ifdef VK_LCONTROL
	ELEMENT(VK_LCONTROL),
#else
	"",
#endif
#ifdef VK_RCONTROL
	ELEMENT(VK_RCONTROL),
#else
	"",
#endif
#ifdef VK_LMENU
	ELEMENT(VK_LMENU),
#else
	"",
#endif
#ifdef VK_RMENU
	ELEMENT(VK_RMENU),
#else
	"",
#endif
#ifdef VK_BROWSER_BACK
	ELEMENT(VK_BROWSER_BACK),
#else
	"",
#endif
#ifdef VK_BROWSER_FORWARD
	ELEMENT(VK_BROWSER_FORWARD),
#else
	"",
#endif
#ifdef VK_BROWSER_REFRESH
	ELEMENT(VK_BROWSER_REFRESH),
#else
	"",
#endif
#ifdef VK_BROWSER_STOP
	ELEMENT(VK_BROWSER_STOP),
#else
	"",
#endif
#ifdef VK_BROWSER_SEARCH
	ELEMENT(VK_BROWSER_SEARCH),
#else
	"",
#endif
#ifdef VK_BROWSER_FAVORITES
	ELEMENT(VK_BROWSER_FAVORITES),
#else
	"",
#endif
#ifdef VK_BROWSER_HOME
	ELEMENT(VK_BROWSER_HOME),
#else
	"",
#endif
#ifdef VK_VOLUME_MUTE
	ELEMENT(VK_VOLUME_MUTE),
#else
	"",
#endif
#ifdef VK_VOLUME_DOWN
	ELEMENT(VK_VOLUME_DOWN),
#else
	"",
#endif
#ifdef VK_VOLUME_UP
	ELEMENT(VK_VOLUME_UP),
#else
	"",
#endif
#ifdef VK_MEDIA_NEXT_TRACK
	ELEMENT(VK_MEDIA_NEXT_TRACK),
#else
	"",
#endif
#ifdef VK_MEDIA_PREV_TRACK
	ELEMENT(VK_MEDIA_PREV_TRACK),
#else
	"",
#endif
#ifdef VK_MEDIA_STOP
	ELEMENT(VK_MEDIA_STOP),
#else
	"",
#endif
#ifdef VK_MEDIA_PLAY_PAUSE
	ELEMENT(VK_MEDIA_PLAY_PAUSE),
#else
	"",
#endif
#ifdef VK_LAUNCH_MAIL
	ELEMENT(VK_LAUNCH_MAIL),
#else
	"",
#endif
#ifdef VK_LAUNCH_MEDIA_SELECT
	ELEMENT(VK_LAUNCH_MEDIA_SELECT),
#else
	"",
#endif
#ifdef VK_LAUNCH_APP1
	ELEMENT(VK_LAUNCH_APP1),
#else
	"",
#endif
#ifdef VK_LAUNCH_APP2
	ELEMENT(VK_LAUNCH_APP2),
#else
	"",
#endif
	"", // 0xB8
	"", // 0xB9
#ifdef VK_OEM_1
	ELEMENT(VK_OEM_1),
#else
	"",
#endif
#ifdef VK_OEM_PLUS
	ELEMENT(VK_OEM_PLUS),
#else
	"",
#endif
#ifdef VK_OEM_COMMA
	ELEMENT(VK_OEM_COMMA),
#else
	"",
#endif
#ifdef VK_OEM_MINUS
	ELEMENT(VK_OEM_MINUS),
#else
	"",
#endif
#ifdef VK_OEM_PERIOD
	ELEMENT(VK_OEM_PERIOD),
#else
	"",
#endif
#ifdef VK_OEM_2
	ELEMENT(VK_OEM_2),
#else
	"",
#endif
#ifdef VK_OEM_3
	ELEMENT(VK_OEM_3),
#else
	"",
#endif
	"", // 0xC1
	"", // 0xC2
#ifdef VK_GAMEPAD_A
	ELEMENT(VK_GAMEPAD_A),
#else
	"",
#endif
#ifdef VK_GAMEPAD_B
	ELEMENT(VK_GAMEPAD_B),
#else
	"",
#endif
#ifdef VK_GAMEPAD_X
	ELEMENT(VK_GAMEPAD_X),
#else
	"",
#endif
#ifdef VK_GAMEPAD_Y
	ELEMENT(VK_GAMEPAD_Y),
#else
	"",
#endif
#ifdef VK_GAMEPAD_RIGHT_SHOULDER
	ELEMENT(VK_GAMEPAD_RIGHT_SHOULDER),
#else
	"",
#endif
#ifdef VK_GAMEPAD_LEFT_SHOULDER
	ELEMENT(VK_GAMEPAD_LEFT_SHOULDER),
#else
	"",
#endif
#ifdef VK_GAMEPAD_LEFT_TRIGGER
	ELEMENT(VK_GAMEPAD_LEFT_TRIGGER),
#else
	"",
#endif
#ifdef VK_GAMEPAD_RIGHT_TRIGGER
	ELEMENT(VK_GAMEPAD_RIGHT_TRIGGER),
#else
	"",
#endif
#ifdef VK_GAMEPAD_DPAD_UP
	ELEMENT(VK_GAMEPAD_DPAD_UP),
#else
	"",
#endif
#ifdef VK_GAMEPAD_DPAD_DOWN
	ELEMENT(VK_GAMEPAD_DPAD_DOWN),
#else
	"",
#endif
#ifdef VK_GAMEPAD_DPAD_LEFT
	ELEMENT(VK_GAMEPAD_DPAD_LEFT),
#else
	"",
#endif
#ifdef VK_GAMEPAD_DPAD_RIGHT
	ELEMENT(VK_GAMEPAD_DPAD_RIGHT),
#else
	"",
#endif
#ifdef VK_GAMEPAD_MENU
	ELEMENT(VK_GAMEPAD_MENU),
#else
	"",
#endif
#ifdef VK_GAMEPAD_VIEW
	ELEMENT(VK_GAMEPAD_VIEW),
#else
	"",
#endif
#ifdef VK_GAMEPAD_LEFT_THUMBSTICK_BUTTON
	ELEMENT(VK_GAMEPAD_LEFT_THUMBSTICK_BUTTON),
#else
	"",
#endif
#ifdef VK_GAMEPAD_RIGHT_THUMBSTICK_BUTTON
	ELEMENT(VK_GAMEPAD_RIGHT_THUMBSTICK_BUTTON),
#else
	"",
#endif
#ifdef VK_GAMEPAD_LEFT_THUMBSTICK_UP
	ELEMENT(VK_GAMEPAD_LEFT_THUMBSTICK_UP),
#else
	"",
#endif
#ifdef VK_GAMEPAD_LEFT_THUMBSTICK_DOWN
	ELEMENT(VK_GAMEPAD_LEFT_THUMBSTICK_DOWN),
#else
	"",
#endif
#ifdef VK_GAMEPAD_LEFT_THUMBSTICK_RIGHT
	ELEMENT(VK_GAMEPAD_LEFT_THUMBSTICK_RIGHT),
#else
	"",
#endif
#ifdef VK_GAMEPAD_LEFT_THUMBSTICK_LEFT
	ELEMENT(VK_GAMEPAD_LEFT_THUMBSTICK_LEFT),
#else
	"",
#endif
#ifdef VK_GAMEPAD_RIGHT_THUMBSTICK_UP
	ELEMENT(VK_GAMEPAD_RIGHT_THUMBSTICK_UP),
#else
	"",
#endif
#ifdef VK_GAMEPAD_RIGHT_THUMBSTICK_DOWN
	ELEMENT(VK_GAMEPAD_RIGHT_THUMBSTICK_DOWN),
#else
	"",
#endif
#ifdef VK_GAMEPAD_RIGHT_THUMBSTICK_RIGHT
	ELEMENT(VK_GAMEPAD_RIGHT_THUMBSTICK_RIGHT),
#else
	"",
#endif
#ifdef VK_GAMEPAD_RIGHT_THUMBSTICK_LEFT
	ELEMENT(VK_GAMEPAD_RIGHT_THUMBSTICK_LEFT),
#else
	"",
#endif
#ifdef VK_OEM_4
	ELEMENT(VK_OEM_4),
#else
	"",
#endif
#ifdef VK_OEM_5
	ELEMENT(VK_OEM_5),
#else
	"",
#endif
#ifdef VK_OEM_6
	ELEMENT(VK_OEM_6),
#else
	"",
#endif
#ifdef VK_OEM_7
	ELEMENT(VK_OEM_7),
#else
	"",
#endif
#ifdef VK_OEM_8
	ELEMENT(VK_OEM_8),
#else
	"",
#endif
	"", // 0xE0
#ifdef VK_OEM_AX
	ELEMENT(VK_OEM_AX),
#else
	"",
#endif
#ifdef VK_OEM_102
	ELEMENT(VK_OEM_102),
#else
	"",
#endif
#ifdef VK_ICO_HELP
	ELEMENT(VK_ICO_HELP),
#else
	"",
#endif
#ifdef VK_ICO_00
	ELEMENT(VK_ICO_00),
#else
	"",
#endif
#ifdef VK_PROCESSKEY
	ELEMENT(VK_PROCESSKEY),
#else
	"",
#endif
#ifdef VK_ICO_CLEAR
	ELEMENT(VK_ICO_CLEAR),
#else
	"",
#endif
#ifdef VK_PACKET
	ELEMENT(VK_PACKET),
#else
	"",
#endif
	"", // 0xE8
#ifdef VK_OEM_RESET
	ELEMENT(VK_OEM_RESET),
#else
	"",
#endif
#ifdef VK_OEM_JUMP
	ELEMENT(VK_OEM_JUMP),
#else
	"",
#endif
#ifdef VK_OEM_PA1
	ELEMENT(VK_OEM_PA1),
#else
	"",
#endif
#ifdef VK_OEM_PA2
	ELEMENT(VK_OEM_PA2),
#else
	"",
#endif
#ifdef VK_OEM_PA3
	ELEMENT(VK_OEM_PA3),
#else
	"",
#endif
#ifdef VK_OEM_WSCTRL
	ELEMENT(VK_OEM_WSCTRL),
#else
	"",
#endif
#ifdef VK_OEM_CUSEL
	ELEMENT(VK_OEM_CUSEL),
#else
	"",
#endif
#ifdef VK_OEM_ATTN
	ELEMENT(VK_OEM_ATTN),
#else
	"",
#endif
#ifdef VK_OEM_FINISH
	ELEMENT(VK_OEM_FINISH),
#else
	"",
#endif
#ifdef VK_OEM_COPY
	ELEMENT(VK_OEM_COPY),
#else
	"",
#endif
#ifdef VK_OEM_AUTO
	ELEMENT(VK_OEM_AUTO),
#else
	"",
#endif
#ifdef VK_OEM_ENLW
	ELEMENT(VK_OEM_ENLW),
#else
	"",
#endif
#ifdef VK_OEM_BACKTAB
	ELEMENT(VK_OEM_BACKTAB),
#else
	"",
#endif
#ifdef VK_ATTN
	ELEMENT(VK_ATTN),
#else
	"",
#endif
#ifdef VK_CRSEL
	ELEMENT(VK_CRSEL),
#else
	"",
#endif
#ifdef VK_EXSEL
	ELEMENT(VK_EXSEL),
#else
	"",
#endif
#ifdef VK_EREOF
	ELEMENT(VK_EREOF),
#else
	"",
#endif
#ifdef VK_PLAY
	ELEMENT(VK_PLAY),
#else
	"",
#endif
#ifdef VK_ZOOM
	ELEMENT(VK_ZOOM),
#else
	"",
#endif
#ifdef VK_NONAME
	ELEMENT(VK_NONAME),
#else
	"",
#endif
#ifdef VK_PA1
	ELEMENT(VK_PA1),
#else
	"",
#endif
#ifdef VK_OEM_CLEAR
	ELEMENT(VK_OEM_CLEAR),
#else
	"",
#endif
	"", // 0xFF
};

int KeyBind::GetValue(const std::string& str)
{
	static const auto isHex = [](const std::string& str) {
		static const std::regex pattern("(0[xX][0-9a-fA-F]{1,2})");
		return std::regex_match(str, pattern);
	};

	char s[64]{};
	static const auto fakeTrim = [&s](const std::string& str) {
		std::copy_if(str.begin(), str.end(), s, [](const char& ch) { return !::isspace(ch);  });
		return s;
	};
	fakeTrim(str);

	int i = 0;
	try
	{
		// if is number
		i = std::stoi(s, 0, isHex(s) ? 16 : 10);
	}
	catch (const std::invalid_argument& _)
	{
		// if is not number
		for (i = 0; ::strcmp(VK_LIST[i], s) && i < VKEY_MAX; ++i);
		if (i >= VKEY_MAX)
			i = 0; // 0 is not a valid VK. using it as disabled. 
	}
	catch (const std::out_of_range& _)
	{
		;
	}

	return i;
}

std::string KeyBind::GetVKString(const int& value)
{
	return VK_LIST[value];
}

