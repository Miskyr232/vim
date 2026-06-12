#pragma once

typedef enum{
    COL_NORMAL = 0,
    COL_INVERT,
    COL_RED,
    COL_GREEN,
    COL_BLUE,
    COL_YELLOW,
}Color;
    
typedef struct{
    char* data;
    Color* fg;
    Color* bg;
    int W;
    int H;
} Buffer;

Buffer* buf_create(int w, int h);
void buf_free(Buffer* buf);
void buf_set(Buffer* buf, int x, int y, char value);
char buf_get(Buffer* buf, int x, int y);
void buf_print(Buffer* buf);
void buf_fill(Buffer* buf, char value);
void buf_set_string(Buffer* buf, int x, int y, const char* str);
void buf_fill_fg(Buffer* buf, Color col);
void buf_set_fg(Buffer* buf, int x, int y, Color col);
void buf_fill_bg(Buffer* buf, Color col);
void buf_set_bg(Buffer* buf, int x, int y, Color col);