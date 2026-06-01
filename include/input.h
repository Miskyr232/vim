#pragma once

typedef enum {
    KEY_UNKNOWN,

    // навигация
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_HOME,
    KEY_END,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,

    // редактирование
    KEY_ENTER,
    KEY_BACKSPACE,
    KEY_DELETE,
    KEY_TAB,
    KEY_ESC,

    // Ctrl+буква
    KEY_CTRL_A,
    KEY_CTRL_B,
    KEY_CTRL_C,
    KEY_CTRL_D,
    KEY_CTRL_E,
    KEY_CTRL_F,
    KEY_CTRL_G,
    KEY_CTRL_H,
    KEY_CTRL_J,
    KEY_CTRL_K,
    KEY_CTRL_L,
    KEY_CTRL_N,
    KEY_CTRL_O,
    KEY_CTRL_P,
    KEY_CTRL_Q,
    KEY_CTRL_R,
    KEY_CTRL_S,
    KEY_CTRL_T,
    KEY_CTRL_U,
    KEY_CTRL_V,
    KEY_CTRL_W,
    KEY_CTRL_X,
    KEY_CTRL_Y,
    KEY_CTRL_Z,

    // F-клавиши
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
} Code;

typedef struct {
    Code code;
    char ch;
} Key;

Key inp_read_key();