#pragma once

typedef struct{
    char* data;
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