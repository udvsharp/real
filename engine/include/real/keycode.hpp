// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_KEYCODE
#define REAL_KEYCODE

#include <ostream>

#include "real/core.hpp"

namespace real {
	enum class key_code : keycode_t {
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	};

	inline std::ostream &operator<<(std::ostream &os, key_code key_code) {
		os << static_cast<int32_t>(key_code);
		return os;
	}
}

// From glfw3.h
#define REAL_KEY_SPACE           ::real::key_code::Space
#define REAL_KEY_APOSTROPHE      ::real::key_code::Apostrophe    /* ' */
#define REAL_KEY_COMMA           ::real::key_code::Comma         /* , */
#define REAL_KEY_MINUS           ::real::key_code::Minus         /* - */
#define REAL_KEY_PERIOD          ::real::key_code::Period        /* . */
#define REAL_KEY_SLASH           ::real::key_code::Slash         /* / */
#define REAL_KEY_0               ::real::key_code::D0
#define REAL_KEY_1               ::real::key_code::D1
#define REAL_KEY_2               ::real::key_code::D2
#define REAL_KEY_3               ::real::key_code::D3
#define REAL_KEY_4               ::real::key_code::D4
#define REAL_KEY_5               ::real::key_code::D5
#define REAL_KEY_6               ::real::key_code::D6
#define REAL_KEY_7               ::real::key_code::D7
#define REAL_KEY_8               ::real::key_code::D8
#define REAL_KEY_9               ::real::key_code::D9
#define REAL_KEY_SEMICOLON       ::real::key_code::Semicolon     /* ; */
#define REAL_KEY_EQUAL           ::real::key_code::Equal         /* = */
#define REAL_KEY_A               ::real::key_code::A
#define REAL_KEY_B               ::real::key_code::B
#define REAL_KEY_C               ::real::key_code::C
#define REAL_KEY_D               ::real::key_code::D
#define REAL_KEY_E               ::real::key_code::E
#define REAL_KEY_F               ::real::key_code::F
#define REAL_KEY_G               ::real::key_code::G
#define REAL_KEY_H               ::real::key_code::H
#define REAL_KEY_I               ::real::key_code::I
#define REAL_KEY_J               ::real::key_code::J
#define REAL_KEY_K               ::real::key_code::K
#define REAL_KEY_L               ::real::key_code::L
#define REAL_KEY_M               ::real::key_code::M
#define REAL_KEY_N               ::real::key_code::N
#define REAL_KEY_O               ::real::key_code::O
#define REAL_KEY_P               ::real::key_code::P
#define REAL_KEY_Q               ::real::key_code::Q
#define REAL_KEY_R               ::real::key_code::R
#define REAL_KEY_S               ::real::key_code::S
#define REAL_KEY_T               ::real::key_code::T
#define REAL_KEY_U               ::real::key_code::U
#define REAL_KEY_V               ::real::key_code::V
#define REAL_KEY_W               ::real::key_code::W
#define REAL_KEY_X               ::real::key_code::X
#define REAL_KEY_Y               ::real::key_code::Y
#define REAL_KEY_Z               ::real::key_code::Z
#define REAL_KEY_LEFT_BRACKET    ::real::key_code::LeftBracket   /* [ */
#define REAL_KEY_BACKSLASH       ::real::key_code::Backslash     /* \ */
#define REAL_KEY_RIGHT_BRACKET   ::real::key_code::RightBracket  /* ] */
#define REAL_KEY_GRAVE_ACCENT    ::real::key_code::GraveAccent   /* ` */
#define REAL_KEY_WORLD_1         ::real::key_code::World1        /* non-US #1 */
#define REAL_KEY_WORLD_2         ::real::key_code::World2        /* non-US #2 */

/* Function keys */
#define REAL_KEY_ESCAPE          ::real::key_code::Escape
#define REAL_KEY_ENTER           ::real::key_code::Enter
#define REAL_KEY_TAB             ::real::key_code::Tab
#define REAL_KEY_BACKSPACE       ::real::key_code::Backspace
#define REAL_KEY_INSERT          ::real::key_code::Insert
#define REAL_KEY_DELETE          ::real::key_code::Delete
#define REAL_KEY_RIGHT           ::real::key_code::Right
#define REAL_KEY_LEFT            ::real::key_code::Left
#define REAL_KEY_DOWN            ::real::key_code::Down
#define REAL_KEY_UP              ::real::key_code::Up
#define REAL_KEY_PAGE_UP         ::real::key_code::PageUp
#define REAL_KEY_PAGE_DOWN       ::real::key_code::PageDown
#define REAL_KEY_HOME            ::real::key_code::Home
#define REAL_KEY_END             ::real::key_code::End
#define REAL_KEY_CAPS_LOCK       ::real::key_code::CapsLock
#define REAL_KEY_SCROLL_LOCK     ::real::key_code::ScrollLock
#define REAL_KEY_NUM_LOCK        ::real::key_code::NumLock
#define REAL_KEY_PRINT_SCREEN    ::real::key_code::PrintScreen
#define REAL_KEY_PAUSE           ::real::key_code::Pause
#define REAL_KEY_F1              ::real::key_code::F1
#define REAL_KEY_F2              ::real::key_code::F2
#define REAL_KEY_F3              ::real::key_code::F3
#define REAL_KEY_F4              ::real::key_code::F4
#define REAL_KEY_F5              ::real::key_code::F5
#define REAL_KEY_F6              ::real::key_code::F6
#define REAL_KEY_F7              ::real::key_code::F7
#define REAL_KEY_F8              ::real::key_code::F8
#define REAL_KEY_F9              ::real::key_code::F9
#define REAL_KEY_F10             ::real::key_code::F10
#define REAL_KEY_F11             ::real::key_code::F11
#define REAL_KEY_F12             ::real::key_code::F12
#define REAL_KEY_F13             ::real::key_code::F13
#define REAL_KEY_F14             ::real::key_code::F14
#define REAL_KEY_F15             ::real::key_code::F15
#define REAL_KEY_F16             ::real::key_code::F16
#define REAL_KEY_F17             ::real::key_code::F17
#define REAL_KEY_F18             ::real::key_code::F18
#define REAL_KEY_F19             ::real::key_code::F19
#define REAL_KEY_F20             ::real::key_code::F20
#define REAL_KEY_F21             ::real::key_code::F21
#define REAL_KEY_F22             ::real::key_code::F22
#define REAL_KEY_F23             ::real::key_code::F23
#define REAL_KEY_F24             ::real::key_code::F24
#define REAL_KEY_F25             ::real::key_code::F25

/* Keypad */
#define REAL_KEY_KP_0            ::real::key_code::KP0
#define REAL_KEY_KP_1            ::real::key_code::KP1
#define REAL_KEY_KP_2            ::real::key_code::KP2
#define REAL_KEY_KP_3            ::real::key_code::KP3
#define REAL_KEY_KP_4            ::real::key_code::KP4
#define REAL_KEY_KP_5            ::real::key_code::KP5
#define REAL_KEY_KP_6            ::real::key_code::KP6
#define REAL_KEY_KP_7            ::real::key_code::KP7
#define REAL_KEY_KP_8            ::real::key_code::KP8
#define REAL_KEY_KP_9            ::real::key_code::KP9
#define REAL_KEY_KP_DECIMAL      ::real::key_code::KPDecimal
#define REAL_KEY_KP_DIVIDE       ::real::key_code::KPDivide
#define REAL_KEY_KP_MULTIPLY     ::real::key_code::KPMultiply
#define REAL_KEY_KP_SUBTRACT     ::real::key_code::KPSubtract
#define REAL_KEY_KP_ADD          ::real::key_code::KPAdd
#define REAL_KEY_KP_ENTER        ::real::key_code::KPEnter
#define REAL_KEY_KP_EQUAL        ::real::key_code::KPEqual

#define REAL_KEY_LEFT_SHIFT      ::real::key_code::LeftShift
#define REAL_KEY_LEFT_CONTROL    ::real::key_code::LeftControl
#define REAL_KEY_LEFT_ALT        ::real::key_code::LeftAlt
#define REAL_KEY_LEFT_SUPER      ::real::key_code::LeftSuper
#define REAL_KEY_RIGHT_SHIFT     ::real::key_code::RightShift
#define REAL_KEY_RIGHT_CONTROL   ::real::key_code::RightControl
#define REAL_KEY_RIGHT_ALT       ::real::key_code::RightAlt
#define REAL_KEY_RIGHT_SUPER     ::real::key_code::RightSuper
#define REAL_KEY_MENU            ::real::key_code::Menu

#endif //REAL_KEYCODE
