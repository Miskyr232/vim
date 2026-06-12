#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"
#include "utils.h"
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
void line_add_line(Line* line, Line* line2);
void line_remove_char(Line* line, Cursor* curs);
char* line_get_string(Line* line);
void line_reserve(Line* line, int new_capacity);
void line_add_text(Line* line, const char* text);

typedef struct Text{
    vec* vector;
    char* hyinya;
} Text;

Text* text_new();
void text_free(Text* text);
void text_add_line(Text* text, const char* inp_line);
char* text_get_line_text(Text* text, int index);
Line* text_get_line(Text* text, int index);
void text_remove(Text* txt, int index);
void text_render(Text* txt, Buffer* buf, Rect rect, Cursor* curs);
void text_load_from_file(Text* txt, const char* name);
void text_merge_lines(Text* txt, int line_index);
void text_set(Text* txt, int i, void* value);
void text_insert_line(Text* txt, int i, Line* line);