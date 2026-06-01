#include "../include/cursor.h"
#include "../include/text.h"
#include "../include/utils.h"
#include <stdlib.h>

Cursor* curs_new(){
    Cursor* curs = (Cursor*)malloc(sizeof(Cursor));
    curs->cursor_x = 0;
    curs->cursor_y = 0;
    curs->global_cursor_x = 0;
    curs->global_cursor_y = 0;
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
            if((curs->cursor_y != 0 || curs->global_cursor_y != 0) && curs->cursor_x + curs->global_cursor_x >= strlen(text_get_line(txt, curs->cursor_y + curs->global_cursor_y - 1))){
                curs->cursor_x = strlen(text_get_line(txt, curs->cursor_y + curs->global_cursor_y - 1));
            }
            if(curs->cursor_y == 0 && curs->global_cursor_y > 0){
                curs->global_cursor_y--;
            } else if(curs->cursor_y == 0){
                break;
            }else {
                curs->cursor_y--;
            }
            break;
        case DOWN:
            if(curs->cursor_y + curs->global_cursor_y != txt->vector->size - 1 && curs->cursor_x + curs->global_cursor_x >= strlen(text_get_line(txt, curs->cursor_y + curs->global_cursor_y + 1))){
                curs->cursor_x = strlen(text_get_line(txt, curs->cursor_y + curs->global_cursor_y + 1));
            }
            if(curs->cursor_y + curs->global_cursor_y >= txt->vector->size - 1){
                curs->global_cursor_x = 0;
                curs->cursor_x = 0;
            }
            if(curs->cursor_y >= txt->vector->size - 1) break;
            if(curs->cursor_y >= buf->H){
                curs->global_cursor_y++;
            } else{
                curs->cursor_y++;
            }
            break;
        case LEFT:
            if (curs->cursor_x == 0 && curs->global_cursor_x > 0){
                curs->global_cursor_x--;
            }else if(curs->cursor_x == 0){
                break;
            } else 
            curs->cursor_x--;
            break;
        case RIGHT:
            if(curs->cursor_x >= strlen(text_get_line(txt, curs->cursor_y + curs->global_cursor_y))){
                break;
            } else if (curs->cursor_x >= buf->W){
                curs->global_cursor_x++;
            } else{
                curs->cursor_x++;
            }
            break;
    }
}