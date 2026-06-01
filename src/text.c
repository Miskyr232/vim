#include "../include/text.h"
#include "../include/cursor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Text* text_new(){
    Text* text = (Text*)malloc(sizeof(Text));
    text->vector = vec_new(sizeof(Line*));
    text->hyinya = malloc(1);
    *text->hyinya = '~';
    return text;
}

Line* line_new(){
    Line* line = (Line*)malloc(sizeof(Line));
    line->data = (char*)malloc(10 * sizeof(char));
    line->capacity = 10;
    line->size = 0;
    return line;
}

void line_free(Line *line){
    free(line->data);
    free(line);
}

void line_set_string(Line *line, const char *text){
    int len = strlen(text);
    if(line->size + len + 1 >= line->capacity){
        int new_capacity = line->capacity * 2;
        if(new_capacity < line->size + len + 1){
            new_capacity = line->size + len + 1 + 32;
        }
        line->data = realloc(line->data, new_capacity);
        line->capacity = new_capacity;
    }
    
    strcpy(line->data, text);
    line->data[len] = '\0';
    line->size = len;
}

void line_add_char(Line *line, const char ch){
    if(line->size + 1 == line->capacity){
        int new_capacity = line->capacity * 2;
        line->data = realloc(line->data, new_capacity);
        line->capacity = new_capacity;
    }
}

void text_free(Text* text){
    for(int i = 0; i < text->vector->size; i++){
        Line** ptr = (Line**)vec_get(text->vector, i);
        line_free(*ptr);
    }
    vec_free(text->vector);
    free(text->hyinya);
    free(text);
}

void text_add_line(Text* text, const char* inp_line){
    Line* line = line_new();
    line_set_string(line, inp_line);
    vec_push_back(text->vector, &line);
}

char* text_get_line(Text* text, int i) {
    if(i < 0 || i >= text->vector->size) return text->hyinya;
    Line** line_ptr_addr = (Line**)vec_get(text->vector, i);
    return (*line_ptr_addr)->data;
}

void text_render(Text* txt, Buffer* buf, Cursor* curs){
    for (int row = curs->global_cursor_y; row < txt->vector->size; row++) {
        char* line = text_get_line(txt, row);
        if(curs->global_cursor_x >= strlen(line)){
            continue;
        }
        for (int col = curs->global_cursor_x; line[col] != '\0'; col++) {
            buf_set(buf, col - curs->global_cursor_x, row - curs->global_cursor_y, line[col]);
        }
    }
}

void text_load_from_file(Text *txt, const char *name){
    FILE* f;
    f = fopen(name, "r");
    if(f == NULL){
        text_add_line(txt, "error open file");
        return;
    }
    int ch; // Важно: используем int, а не char
    char line[1024]; // Буфер для одной строки (максимум 1023 символа + \0)

    // fgets читает до \n или до конца буфера
    while (fgets(line, sizeof(line), f) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        text_add_line(txt, line);
    }

    fclose(f);
}