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
    return curs;
}

void curs_free(Cursor *curs){
    free(curs);
}

void curs_render(Cursor* curs, Buffer* buf){
    buf_set(buf, curs->cursor_x, curs->cursor_y, '_');
}

void curs_move(Cursor *curs, Text* txt, Buffer* buf, Dirs dir){
    switch (dir) {
        case UP:
            if(curs->cursor_y == 0 && curs->scroll_y == 0) break;
            int global_y = curs->cursor_y + curs->scroll_y;
            int global_x = curs->cursor_x + curs->scroll_x;
            int len_top_line = strlen(text_get_line_text(txt, global_y - 1));
            if(global_x > len_top_line){
                curs->cursor_x = len_top_line;
                curs->scroll_x = 0;
            }
            if (curs->cursor_y == 0) curs->scroll_y--;
            else curs->cursor_y--;
            break;        
        case DOWN:
            int len_down_line = strlen(text_get_line_text(txt, curs->cursor_y + curs->scroll_y + 1));
            if((curs->cursor_y != buf->H - 1 || curs->scroll_y != txt->vector->size - 1) && curs->cursor_x + curs->scroll_x >= len_down_line){
                curs->cursor_x = len_down_line;
                if(len_down_line >= buf->W){
                    curs->scroll_x = len_top_line - buf->W; 
                } else{
                    curs->scroll_x = 0;
                }
            } else if(curs->cursor_y == buf->H - 1){
                curs->scroll_y++;
                break;
            }
            if(curs->scroll_y + curs->cursor_y != txt->vector->size - 1){
                curs->cursor_y++;
            }
            break;
        case LEFT:
            if (curs->cursor_x == 0 && curs->scroll_x > 0){
                curs->scroll_x--;
            }else if(curs->cursor_x == 0){
                break;
            } else 
            curs->cursor_x--;
            break;
        case RIGHT:
            if(curs->cursor_x + curs->scroll_x >= strlen(text_get_line_text(txt, curs->cursor_y + curs->scroll_y))){
                break;
            } else if (curs->cursor_x >= buf->W){
                curs->scroll_x++;
            } else{
                curs->cursor_x++;
            }
            break;
    }
}

void curs_add_char(Cursor *curs, Text *txt, Buffer *buf, const char ch){
    Line* line = text_get_line(txt, curs->scroll_y + curs->cursor_y);
    line_add_char(line, curs->scroll_x + curs->cursor_x, ch);
    curs_move(curs, txt, buf, RIGHT);
}

void curs_backspace(Cursor *curs, Text *txt, Buffer *buf){
    Line* line = text_get_line(txt, curs->scroll_y + curs->cursor_y);
    if(line->size == 0) return;

}