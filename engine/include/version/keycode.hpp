// Copyright (c) 2020 udv. All rights reserved.

#ifndef VN_KEYCODE
#define VN_KEYCODE

#include <ostream>

namespace vn {
    using keycode_t = int;

    enum class key_code : keycode_t {
        // From glfw3.h
        Space               = 32,
        Apostrophe          = 39, /* ' */
        Comma               = 44, /* , */
        Minus               = 45, /* - */
        Period              = 46, /* . */
        Slash               = 47, /* / */

        D0                  = 48, /* 0 */
        D1                  = 49, /* 1 */
        D2                  = 50, /* 2 */
        D3                  = 51, /* 3 */
        D4                  = 52, /* 4 */
        D5                  = 53, /* 5 */
        D6                  = 54, /* 6 */
        D7                  = 55, /* 7 */
        D8                  = 56, /* 8 */
        D9                  = 57, /* 9 */

        Semicolon           = 59, /* ; */
        Equal               = 61, /* = */

        A                   = 65,
        B                   = 66,
        C                   = 67,
        D                   = 68,
        E                   = 69,
        F                   = 70,
        G                   = 71,
        H                   = 72,
        I                   = 73,
        J                   = 74,
        K                   = 75,
        L                   = 76,
        M                   = 77,
        N                   = 78,
        O                   = 79,
        P                   = 80,
        Q                   = 81,
        R                   = 82,
        S                   = 83,
        T                   = 84,
        U                   = 85,
        V                   = 86,
        W                   = 87,
        X                   = 88,
        Y                   = 89,
        Z                   = 90,

        LeftBracket         = 91,  /* [ */
        Backslash           = 92,  /* \ */
        RightBracket        = 93,  /* ] */
        GraveAccent         = 96,  /* ` */

        World1              = 161, /* non-US #1 */
        World2              = 162, /* non-US #2 */

        /* Function keys */
        Escape              = 256,
        Enter               = 257,
        Tab                 = 258,
        Backspace           = 259,
        Insert              = 260,
        Delete              = 261,
        Right               = 262,
        Left                = 263,
        Down                = 264,
        Up                  = 265,
        PageUp              = 266,
        PageDown            = 267,
        Home                = 268,
        End                 = 269,
        CapsLock            = 280,
        ScrollLock          = 281,
        NumLock             = 282,
        PrintScreen         = 283,
        Pause               = 284,
        F1                  = 290,
        F2                  = 291,
        F3                  = 292,
        F4                  = 293,
        F5                  = 294,
        F6                  = 295,
        F7                  = 296,
        F8                  = 297,
        F9                  = 298,
        F10                 = 299,
        F11                 = 300,
        F12                 = 301,
        F13                 = 302,
        F14                 = 303,
        F15                 = 304,
        F16                 = 305,
        F17                 = 306,
        F18                 = 307,
        F19                 = 308,
        F20                 = 309,
        F21                 = 310,
        F22                 = 311,
        F23                 = 312,
        F24                 = 313,
        F25                 = 314,

        /* Keypad */
        KP0                 = 320,
        KP1                 = 321,
        KP2                 = 322,
        KP3                 = 323,
        KP4                 = 324,
        KP5                 = 325,
        KP6                 = 326,
        KP7                 = 327,
        KP8                 = 328,
        KP9                 = 329,
        KPDecimal           = 330,
        KPDivide            = 331,
        KPMultiply          = 332,
        KPSubtract          = 333,
        KPAdd               = 334,
        KPEnter             = 335,
        KPEqual             = 336,

        LeftShift           = 340,
        LeftControl         = 341,
        LeftAlt             = 342,
        LeftSuper           = 343,
        RightShift          = 344,
        RightControl        = 345,
        RightAlt            = 346,
        RightSuper          = 347,
        Menu                = 348
    };

    inline std::ostream& operator<<(std::ostream& os, key_code key_code)
    {
        os << static_cast<int32_t>(key_code);
        return os;
    }
}

// From glfw3.h
#define VN_KEY_SPACE           ::vn::key_code::Space
#define VN_KEY_APOSTROPHE      ::vn::key_code::Apostrophe    /* ' */
#define VN_KEY_COMMA           ::vn::key_code::Comma         /* , */
#define VN_KEY_MINUS           ::vn::key_code::Minus         /* - */
#define VN_KEY_PERIOD          ::vn::key_code::Period        /* . */
#define VN_KEY_SLASH           ::vn::key_code::Slash         /* / */
#define VN_KEY_0               ::vn::key_code::D0
#define VN_KEY_1               ::vn::key_code::D1
#define VN_KEY_2               ::vn::key_code::D2
#define VN_KEY_3               ::vn::key_code::D3
#define VN_KEY_4               ::vn::key_code::D4
#define VN_KEY_5               ::vn::key_code::D5
#define VN_KEY_6               ::vn::key_code::D6
#define VN_KEY_7               ::vn::key_code::D7
#define VN_KEY_8               ::vn::key_code::D8
#define VN_KEY_9               ::vn::key_code::D9
#define VN_KEY_SEMICOLON       ::vn::key_code::Semicolon     /* ; */
#define VN_KEY_EQUAL           ::vn::key_code::Equal         /* = */
#define VN_KEY_A               ::vn::key_code::A
#define VN_KEY_B               ::vn::key_code::B
#define VN_KEY_C               ::vn::key_code::C
#define VN_KEY_D               ::vn::key_code::D
#define VN_KEY_E               ::vn::key_code::E
#define VN_KEY_F               ::vn::key_code::F
#define VN_KEY_G               ::vn::key_code::G
#define VN_KEY_H               ::vn::key_code::H
#define VN_KEY_I               ::vn::key_code::I
#define VN_KEY_J               ::vn::key_code::J
#define VN_KEY_K               ::vn::key_code::K
#define VN_KEY_L               ::vn::key_code::L
#define VN_KEY_M               ::vn::key_code::M
#define VN_KEY_N               ::vn::key_code::N
#define VN_KEY_O               ::vn::key_code::O
#define VN_KEY_P               ::vn::key_code::P
#define VN_KEY_Q               ::vn::key_code::Q
#define VN_KEY_R               ::vn::key_code::R
#define VN_KEY_S               ::vn::key_code::S
#define VN_KEY_T               ::vn::key_code::T
#define VN_KEY_U               ::vn::key_code::U
#define VN_KEY_V               ::vn::key_code::V
#define VN_KEY_W               ::vn::key_code::W
#define VN_KEY_X               ::vn::key_code::X
#define VN_KEY_Y               ::vn::key_code::Y
#define VN_KEY_Z               ::vn::key_code::Z
#define VN_KEY_LEFT_BRACKET    ::vn::key_code::LeftBracket   /* [ */
#define VN_KEY_BACKSLASH       ::vn::key_code::Backslash     /* \ */
#define VN_KEY_RIGHT_BRACKET   ::vn::key_code::RightBracket  /* ] */
#define VN_KEY_GRAVE_ACCENT    ::vn::key_code::GraveAccent   /* ` */
#define VN_KEY_WORLD_1         ::vn::key_code::World1        /* non-US #1 */
#define VN_KEY_WORLD_2         ::vn::key_code::World2        /* non-US #2 */

/* Function keys */
#define VN_KEY_ESCAPE          ::vn::key_code::Escape
#define VN_KEY_ENTER           ::vn::key_code::Enter
#define VN_KEY_TAB             ::vn::key_code::Tab
#define VN_KEY_BACKSPACE       ::vn::key_code::Backspace
#define VN_KEY_INSERT          ::vn::key_code::Insert
#define VN_KEY_DELETE          ::vn::key_code::Delete
#define VN_KEY_RIGHT           ::vn::key_code::Right
#define VN_KEY_LEFT            ::vn::key_code::Left
#define VN_KEY_DOWN            ::vn::key_code::Down
#define VN_KEY_UP              ::vn::key_code::Up
#define VN_KEY_PAGE_UP         ::vn::key_code::PageUp
#define VN_KEY_PAGE_DOWN       ::vn::key_code::PageDown
#define VN_KEY_HOME            ::vn::key_code::Home
#define VN_KEY_END             ::vn::key_code::End
#define VN_KEY_CAPS_LOCK       ::vn::key_code::CapsLock
#define VN_KEY_SCROLL_LOCK     ::vn::key_code::ScrollLock
#define VN_KEY_NUM_LOCK        ::vn::key_code::NumLock
#define VN_KEY_PRINT_SCREEN    ::vn::key_code::PrintScreen
#define VN_KEY_PAUSE           ::vn::key_code::Pause
#define VN_KEY_F1              ::vn::key_code::F1
#define VN_KEY_F2              ::vn::key_code::F2
#define VN_KEY_F3              ::vn::key_code::F3
#define VN_KEY_F4              ::vn::key_code::F4
#define VN_KEY_F5              ::vn::key_code::F5
#define VN_KEY_F6              ::vn::key_code::F6
#define VN_KEY_F7              ::vn::key_code::F7
#define VN_KEY_F8              ::vn::key_code::F8
#define VN_KEY_F9              ::vn::key_code::F9
#define VN_KEY_F10             ::vn::key_code::F10
#define VN_KEY_F11             ::vn::key_code::F11
#define VN_KEY_F12             ::vn::key_code::F12
#define VN_KEY_F13             ::vn::key_code::F13
#define VN_KEY_F14             ::vn::key_code::F14
#define VN_KEY_F15             ::vn::key_code::F15
#define VN_KEY_F16             ::vn::key_code::F16
#define VN_KEY_F17             ::vn::key_code::F17
#define VN_KEY_F18             ::vn::key_code::F18
#define VN_KEY_F19             ::vn::key_code::F19
#define VN_KEY_F20             ::vn::key_code::F20
#define VN_KEY_F21             ::vn::key_code::F21
#define VN_KEY_F22             ::vn::key_code::F22
#define VN_KEY_F23             ::vn::key_code::F23
#define VN_KEY_F24             ::vn::key_code::F24
#define VN_KEY_F25             ::vn::key_code::F25

/* Keypad */
#define VN_KEY_KP_0            ::vn::key_code::KP0
#define VN_KEY_KP_1            ::vn::key_code::KP1
#define VN_KEY_KP_2            ::vn::key_code::KP2
#define VN_KEY_KP_3            ::vn::key_code::KP3
#define VN_KEY_KP_4            ::vn::key_code::KP4
#define VN_KEY_KP_5            ::vn::key_code::KP5
#define VN_KEY_KP_6            ::vn::key_code::KP6
#define VN_KEY_KP_7            ::vn::key_code::KP7
#define VN_KEY_KP_8            ::vn::key_code::KP8
#define VN_KEY_KP_9            ::vn::key_code::KP9
#define VN_KEY_KP_DECIMAL      ::vn::key_code::KPDecimal
#define VN_KEY_KP_DIVIDE       ::vn::key_code::KPDivide
#define VN_KEY_KP_MULTIPLY     ::vn::key_code::KPMultiply
#define VN_KEY_KP_SUBTRACT     ::vn::key_code::KPSubtract
#define VN_KEY_KP_ADD          ::vn::key_code::KPAdd
#define VN_KEY_KP_ENTER        ::vn::key_code::KPEnter
#define VN_KEY_KP_EQUAL        ::vn::key_code::KPEqual

#define VN_KEY_LEFT_SHIFT      ::vn::key_code::LeftShift
#define VN_KEY_LEFT_CONTROL    ::vn::key_code::LeftControl
#define VN_KEY_LEFT_ALT        ::vn::key_code::LeftAlt
#define VN_KEY_LEFT_SUPER      ::vn::key_code::LeftSuper
#define VN_KEY_RIGHT_SHIFT     ::vn::key_code::RightShift
#define VN_KEY_RIGHT_CONTROL   ::vn::key_code::RightControl
#define VN_KEY_RIGHT_ALT       ::vn::key_code::RightAlt
#define VN_KEY_RIGHT_SUPER     ::vn::key_code::RightSuper
#define VN_KEY_MENU            ::vn::key_code::Menu

#endif //VN_KEYCODE
