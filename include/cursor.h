#pragma once

#include "buffer.h"
#include "utils.h"
#include <stdlib.h>

typedef struct Text Text;

typedef struct Cursor_s{
    int cursor_x;
    int cursor_y;
    int global_cursor_x;
    int global_cursor_y;
} Cursor;

Cursor* curs_new();
void curs_free(Cursor* curs);
void curs_render(Cursor* curs, Buffer* buf);
void curs_move(Cursor *curs, Text* txt, Buffer* buf, Dirs dir);
void curs_add_char(Cursor* curs, Text* txt, Buffer* buf);