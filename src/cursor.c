#include "../include/cursor.h"
#include "../include/text.h"
#include "../include/utils.h"
#include <stdlib.h>

Cursor* curs_new(){
    Cursor* curs = (Cursor*)malloc(sizeof(Cursor));
    curs->cursor_x = 0;
    curs->cursor_y = 0;
    curs->scroll_x = 0;
    curs->scroll_y = 0;
    curs->wanted_x = 0;
    curs->wanted_y = 0;
    return curs;
}

void curs_free(Cursor *curs){
    free(curs);
}

void curs_render(Cursor* curs, Buffer* buf){
    buf_set(buf, curs->cursor_x, curs->cursor_y, '_');
}

void curs_move(Cursor *curs, Text* txt, Buffer* buf, Dirs dir){
    int global_x, global_y;
    int target_x;
    global_y = curs->cursor_y + curs->scroll_y;
    global_x = curs->cursor_x + curs->scroll_x;

    switch (dir) {
        case UP:
            if(curs->cursor_y == 0 && curs->scroll_y == 0) break;
            int len_top_line = strlen(text_get_line_text(txt, global_y - 1));
            target_x = curs->wanted_x < len_top_line ? curs->wanted_x : len_top_line;
            if (target_x < buf->W) {
                curs->cursor_x = target_x;
                curs->scroll_x = 0;
            } else {
                curs->cursor_x = buf->W - 1;
                curs->scroll_x = target_x - (buf->W - 1);
            }
            if (curs->cursor_y == 0) curs->scroll_y--;
            else curs->cursor_y--;
            break;
        case DOWN:
            if(global_y >= txt->vector->size - 1) break;
            int len_down_line = strlen(text_get_line_text(txt, global_y + 1));
            int target_x = curs->wanted_x < len_down_line ? curs->wanted_x : len_down_line;
            if (target_x < buf->W) {
                curs->cursor_x = target_x;
                curs->scroll_x = 0;
            } else {
                curs->cursor_x = buf->W - 1;
                curs->scroll_x = target_x - (buf->W - 1);
            }
            if (curs->cursor_y == buf->H - 1) curs->scroll_y++;
            else curs->cursor_y++;
            break;
        case LEFT:
            if(curs->cursor_x == 0 && curs->scroll_x == 0)
                break;
            if(curs->cursor_x == 0 && curs->scroll_x > 0)
                curs->scroll_x--;
            else
                curs->cursor_x--;
            curs->wanted_x = curs->cursor_x + curs->scroll_x;
            break;
        case RIGHT:
            int len_line = strlen(text_get_line_text(txt, global_y));
            if(global_x >= len_line)
                break;
            if(curs->cursor_x == buf->W - 1)
                curs->scroll_x++;
            else
                curs->cursor_x++;
            curs->wanted_x = curs->cursor_x + curs->scroll_x;
            break;
    }
}

void curs_add_char(Cursor *curs, Text *txt, Buffer *buf, const char ch){
    Line* line = text_get_line(txt, curs->scroll_y + curs->cursor_y);
    line_add_char(line, curs->scroll_x + curs->cursor_x, ch);
    curs_move(curs, txt, buf, RIGHT);
}

void curs_to_end(Cursor *curs, Text *txt, Buffer *buf){
    int end_index = text_get_line(txt, curs->cursor_y + curs->scroll_y)->size;
    curs->cursor_x = end_index;
}

void curs_set_x(Cursor *curs, Text* txt, Buffer *buf, int index){
    int global_x = curs->cursor_x + curs->scroll_x;
    int global_y = curs->cursor_y + curs->scroll_y;
    if(index > text_get_line(txt, global_y)->size) return;
    curs->cursor_x = index;
}

void curs_backspace(Cursor *curs, Text *txt, Buffer *buf){
    int global_y = curs->cursor_y + curs->scroll_y;
    int global_x = curs->cursor_x + curs->scroll_x;
    if(global_y == 0 && global_x == 0) return;
    Line* line = text_get_line(txt, global_y);
    Line* up_line = text_get_line(txt, global_y - 1);
    if(line->size == 0){
        text_remove(txt, global_y);
        curs_move(curs, txt, buf, UP);
    }else if(global_x == 0){
        int old_size = up_line->size;
        text_merge_lines(txt, global_y);
        curs_move(curs, txt, buf, UP);
        curs_set_x(curs, txt, buf, old_size);
    }else{
        line_remove_char(line, curs);
        curs_move(curs, txt, buf, LEFT);
    }
}