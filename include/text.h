#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"
#include "vector.h"

typedef struct Cursor_s Cursor;


typedef struct{
    char* data;
    int size;
    int capacity;
} Line;

Line* line_new();
void line_free(Line* line);
void line_set_string(Line* line, const char* text);
void line_add_char(Line* line, int index, const char ch);
void line_remove_char(Line* line, Cursor* cursm);
char* line_get_string();

typedef struct Text{
    vec* vector;
    char* hyinya;
} Text;

Text* text_new();
void text_free(Text* text);
void text_add_line(Text* text, const char* inp_line);
char* text_get_line_text(Text* text, int index);
Line* text_get_line(Text* text, int index);
void text_render(Text* txt, Buffer* buf, Cursor* curs);
void text_load_from_file(Text* txt, const char* name);