// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_KEYCODE
#define REAL_KEYCODE

#include <ostream>

#include "real/core.hpp"

namespace Real {
	enum class KeyCode : keycode_t {
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

	inline std::ostream &operator<<(std::ostream &os, KeyCode keyCode) {
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define REAL_KEY_SPACE           ::Real::KeyCode::Space
#define REAL_KEY_APOSTROPHE      ::real::KeyCode::Apostrophe    /* ' */
#define REAL_KEY_COMMA           ::real::KeyCode::Comma         /* , */
#define REAL_KEY_MINUS           ::real::KeyCode::Minus         /* - */
#define REAL_KEY_PERIOD          ::real::KeyCode::Period        /* . */
#define REAL_KEY_SLASH           ::real::KeyCode::Slash         /* / */
#define REAL_KEY_0               ::real::KeyCode::D0
#define REAL_KEY_1               ::real::KeyCode::D1
#define REAL_KEY_2               ::real::KeyCode::D2
#define REAL_KEY_3               ::real::KeyCode::D3
#define REAL_KEY_4               ::real::KeyCode::D4
#define REAL_KEY_5               ::real::KeyCode::D5
#define REAL_KEY_6               ::real::KeyCode::D6
#define REAL_KEY_7               ::real::KeyCode::D7
#define REAL_KEY_8               ::real::KeyCode::D8
#define REAL_KEY_9               ::real::KeyCode::D9
#define REAL_KEY_SEMICOLON       ::real::KeyCode::Semicolon     /* ; */
#define REAL_KEY_EQUAL           ::real::KeyCode::Equal         /* = */
#define REAL_KEY_A               ::Real::KeyCode::A
#define REAL_KEY_B               ::real::KeyCode::B
#define REAL_KEY_C               ::Real::KeyCode::C
#define REAL_KEY_D               ::real::KeyCode::D
#define REAL_KEY_E               ::real::KeyCode::E
#define REAL_KEY_F               ::real::KeyCode::F
#define REAL_KEY_G               ::real::KeyCode::G
#define REAL_KEY_H               ::real::KeyCode::H
#define REAL_KEY_I               ::real::KeyCode::I
#define REAL_KEY_J               ::real::KeyCode::J
#define REAL_KEY_K               ::real::KeyCode::K
#define REAL_KEY_L               ::real::KeyCode::L
#define REAL_KEY_M               ::real::KeyCode::M
#define REAL_KEY_N               ::real::KeyCode::N
#define REAL_KEY_O               ::real::KeyCode::O
#define REAL_KEY_P               ::real::KeyCode::P
#define REAL_KEY_Q               ::real::KeyCode::Q
#define REAL_KEY_R               ::real::KeyCode::R
#define REAL_KEY_S               ::real::KeyCode::S
#define REAL_KEY_T               ::real::KeyCode::T
#define REAL_KEY_U               ::real::KeyCode::U
#define REAL_KEY_V               ::Real::KeyCode::V
#define REAL_KEY_W               ::real::KeyCode::W
#define REAL_KEY_X               ::Real::KeyCode::X
#define REAL_KEY_Y               ::Real::KeyCode::Y
#define REAL_KEY_Z               ::Real::KeyCode::Z
#define REAL_KEY_LEFT_BRACKET    ::real::KeyCode::LeftBracket   /* [ */
#define REAL_KEY_BACKSLASH       ::real::KeyCode::Backslash     /* \ */
#define REAL_KEY_RIGHT_BRACKET   ::real::KeyCode::RightBracket  /* ] */
#define REAL_KEY_GRAVE_ACCENT    ::real::KeyCode::GraveAccent   /* ` */
#define REAL_KEY_WORLD_1         ::real::KeyCode::World1        /* non-US #1 */
#define REAL_KEY_WORLD_2         ::real::KeyCode::World2        /* non-US #2 */

/* Function keys */
#define REAL_KEY_ESCAPE          ::Real::KeyCode::Escape
#define REAL_KEY_ENTER           ::Real::KeyCode::Enter
#define REAL_KEY_TAB             ::Real::KeyCode::Tab
#define REAL_KEY_BACKSPACE       ::Real::KeyCode::Backspace
#define REAL_KEY_INSERT          ::Real::KeyCode::Insert
#define REAL_KEY_DELETE          ::Real::KeyCode::Delete
#define REAL_KEY_RIGHT           ::Real::KeyCode::Right
#define REAL_KEY_LEFT            ::Real::KeyCode::Left
#define REAL_KEY_DOWN            ::Real::KeyCode::Down
#define REAL_KEY_UP              ::Real::KeyCode::Up
#define REAL_KEY_PAGE_UP         ::Real::KeyCode::PageUp
#define REAL_KEY_PAGE_DOWN       ::Real::KeyCode::PageDown
#define REAL_KEY_HOME            ::Real::KeyCode::Home
#define REAL_KEY_END             ::Real::KeyCode::End
#define REAL_KEY_CAPS_LOCK       ::real::KeyCode::CapsLock
#define REAL_KEY_SCROLL_LOCK     ::real::KeyCode::ScrollLock
#define REAL_KEY_NUM_LOCK        ::real::KeyCode::NumLock
#define REAL_KEY_PRINT_SCREEN    ::real::KeyCode::PrintScreen
#define REAL_KEY_PAUSE           ::real::KeyCode::Pause
#define REAL_KEY_F1              ::real::KeyCode::F1
#define REAL_KEY_F2              ::real::KeyCode::F2
#define REAL_KEY_F3              ::real::KeyCode::F3
#define REAL_KEY_F4              ::real::KeyCode::F4
#define REAL_KEY_F5              ::real::KeyCode::F5
#define REAL_KEY_F6              ::real::KeyCode::F6
#define REAL_KEY_F7              ::real::KeyCode::F7
#define REAL_KEY_F8              ::real::KeyCode::F8
#define REAL_KEY_F9              ::real::KeyCode::F9
#define REAL_KEY_F10             ::real::KeyCode::F10
#define REAL_KEY_F11             ::real::KeyCode::F11
#define REAL_KEY_F12             ::real::KeyCode::F12
#define REAL_KEY_F13             ::real::KeyCode::F13
#define REAL_KEY_F14             ::real::KeyCode::F14
#define REAL_KEY_F15             ::real::KeyCode::F15
#define REAL_KEY_F16             ::real::KeyCode::F16
#define REAL_KEY_F17             ::real::KeyCode::F17
#define REAL_KEY_F18             ::real::KeyCode::F18
#define REAL_KEY_F19             ::real::KeyCode::F19
#define REAL_KEY_F20             ::real::KeyCode::F20
#define REAL_KEY_F21             ::real::KeyCode::F21
#define REAL_KEY_F22             ::real::KeyCode::F22
#define REAL_KEY_F23             ::real::KeyCode::F23
#define REAL_KEY_F24             ::real::KeyCode::F24
#define REAL_KEY_F25             ::real::KeyCode::F25

/* Keypad */
#define REAL_KEY_KP_0            ::real::KeyCode::KP0
#define REAL_KEY_KP_1            ::real::KeyCode::KP1
#define REAL_KEY_KP_2            ::real::KeyCode::KP2
#define REAL_KEY_KP_3            ::real::KeyCode::KP3
#define REAL_KEY_KP_4            ::real::KeyCode::KP4
#define REAL_KEY_KP_5            ::real::KeyCode::KP5
#define REAL_KEY_KP_6            ::real::KeyCode::KP6
#define REAL_KEY_KP_7            ::real::KeyCode::KP7
#define REAL_KEY_KP_8            ::real::KeyCode::KP8
#define REAL_KEY_KP_9            ::real::KeyCode::KP9
#define REAL_KEY_KP_DECIMAL      ::real::KeyCode::KPDecimal
#define REAL_KEY_KP_DIVIDE       ::real::KeyCode::KPDivide
#define REAL_KEY_KP_MULTIPLY     ::real::KeyCode::KPMultiply
#define REAL_KEY_KP_SUBTRACT     ::real::KeyCode::KPSubtract
#define REAL_KEY_KP_ADD          ::real::KeyCode::KPAdd
#define REAL_KEY_KP_ENTER        ::Real::KeyCode::KPEnter
#define REAL_KEY_KP_EQUAL        ::real::KeyCode::KPEqual

#define REAL_KEY_LEFT_SHIFT      ::Real::KeyCode::LeftShift
#define REAL_KEY_LEFT_CONTROL    ::Real::KeyCode::LeftControl
#define REAL_KEY_LEFT_ALT        ::Real::KeyCode::LeftAlt
#define REAL_KEY_LEFT_SUPER      ::Real::KeyCode::LeftSuper
#define REAL_KEY_RIGHT_SHIFT     ::Real::KeyCode::RightShift
#define REAL_KEY_RIGHT_CONTROL   ::Real::KeyCode::RightControl
#define REAL_KEY_RIGHT_ALT       ::Real::KeyCode::RightAlt
#define REAL_KEY_RIGHT_SUPER     ::Real::KeyCode::RightSuper
#define REAL_KEY_MENU            ::real::KeyCode::Menu

#endif //REAL_KEYCODE
