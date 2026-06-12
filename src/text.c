#include "../include/text.h"
#include "../include/cursor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Text* text_new(){
    Text* text = (Text*)malloc(sizeof(Text));
    text->vector = vec_new(sizeof(Line*));
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

void line_add_char(Line *line, int index, const char ch){
    if(line->size + 1 == line->capacity){
        int new_capacity = line->capacity * 2;
        line->data = realloc(line->data, new_capacity);
        line->capacity = new_capacity;
    }

    if (index < line->size) {
        memmove(&line->data[index + 1], &line->data[index], line->size - index + 1);
    }

    line->data[index] = ch;
    line->size++;
    line->data[line->size] = '\0';
}

void line_remove_char(Line *line, Cursor* curs) {
    int global_x = curs->cursor_x + curs->scroll_x;
    if (line->size == 0 || global_x <= 0) return;
    memmove(&line->data[global_x - 1], &line->data[global_x], line->size - global_x + 1);
    line->size--;
}

void line_add_line(Line *line, Line *line2){
    if(line->capacity < line2->size + line->size + 1){
        int new_capacity = (line->size + line2->size) * 2;
        line->capacity = new_capacity;
        line->data = realloc(line->data, line->capacity * sizeof(char));
    }
    memmove(&line->data[line->size], line2->data, line2->size + 1);

    line->size = line->size + line2->size;
}

void line_reserve(Line *line, int new_capacity){
    if(line->capacity < new_capacity){
        line->capacity = new_capacity;
        line->data = realloc(line->data, line->capacity * sizeof(char));
    }
}
char* line_get_string(Line* line){
    return line->data;
}

void line_add_text(Line *line, const char *text){
    int text_size = strlen(text);
    if(line->capacity < line->size + text_size + 1){
        int new_capacity = (line->size + text_size + 16);
        line->capacity = new_capacity;
        line->data = realloc(line->data, line->capacity * sizeof(char));
    }
    memcpy(&line->data[line->size], text, text_size + 1);
    line->size = line->size + text_size;
}

void text_set(Text *txt, int i, void* value){
    memcpy(vec_get(txt->vector, i), value, txt->vector->element_size); 
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

void text_insert_line(Text *txt, int i, Line* line){
    vec_insert(txt->vector, i, (void*)&line);
}

void text_add_line(Text* text, const char* inp_line){
    Line* line = line_new();
    line_set_string(line, inp_line);
    vec_push_back(text->vector, &line);
}

void text_remove(Text *txt, int index){
    vec_remove(txt->vector, index);
}

char* text_get_line_text(Text* text, int index) {
    Line* l = text_get_line(text, index);
    return (l != NULL) ? l->data : NULL;
}

void text_render(Text* txt, Buffer*buf, Rect rect, Cursor* curs) {
    if (txt == NULL || txt->vector == NULL) return;

    for (int row = curs->scroll_y; row < txt->vector->size; row++) {
        // 1. Получаем указатель на строку
        char* line = text_get_line_text(txt, row);
        
        // 2. ЗАЩИТА: если строка NULL, пропускаем или прерываем
        if (line == NULL) {
            continue; 
        }

        // 3. Безопасное вычисление длины
        int len = strlen(line);
        if (curs->scroll_x >= len) {
            continue;
        }

        // 4. Отрисовка символов
        for (int col = curs->scroll_x; line[col] != '\0'; col++) {
            // Важно: проверяем границы буфера, чтобы не писать "в никуда"
            if (col - curs->scroll_x >= rect.w || row - curs->scroll_y >= rect.h) {
                break; 
            }
            buf_set(buf, col - curs->scroll_x, row - curs->scroll_y, line[col]);
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
    int ch;
    char line[1024]; //buffer

    while (fgets(line, sizeof(line), f) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        text_add_line(txt, line);
    }

    fclose(f);
}

Line* text_get_line(Text* txt, int index){
    return *(Line**)vec_get(txt->vector, index);
}

void text_merge_lines(Text* txt, int line_index) {
    if(line_index == 0) return;
    Line* src = text_get_line(txt, line_index);
    Line* dest = text_get_line(txt, line_index - 1);
    line_add_line(dest, src);
    text_remove(txt, line_index);
}