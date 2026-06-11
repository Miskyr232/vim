#pragma once

#include "buffer.h"
#include "utils.h"
#include <stdlib.h>

typedef struct Text Text;

typedef struct Cursor_s{
    int cursor_x;
    int cursor_y;

    int scroll_x;
    int scroll_y;

    int wanted_x;
    int wanted_y;
} Cursor;

Cursor* curs_new();
void curs_free(Cursor* curs);
void curs_render(Cursor* curs, Buffer* buf);
void curs_move(Cursor *curs, Text* txt, Buffer* buf, Dirs dir);
void curs_add_char(Cursor* curs, Text* txt, Buffer* buf, char ch);
void curs_backspace(Cursor* curs, Text* txt, Buffer* buf);
void curs_to_end(Cursor* curs, Text* txt, Buffer* buf);
void curs_set_x(Cursor* curs, Text* txt, Buffer* buf, int x);
void curs_enter(Cursor* curs, Text* txt, Buffer* buf);