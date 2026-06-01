#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "../include/buffer.h"
#include "../include/terminal.h"
#include "../include/input.h"
#include "../include/vector.h"
#include "../include/text.h"
#include "../include/cursor.h"

int main(){
    term_enable_raw();
    int W, H;
    term_get_size(&H, &W);
    W -= 2;
    H -= 2;
    Buffer* buf = buf_create(W, H);
    Text* txt = text_new();
    Cursor* curs = curs_new();
    text_add_line(txt, "Hello привет");
    text_load_from_file(txt, "./src/main.c");
    
    term_clear();

    while(1){
        term_cursor_to_start();
        buf_fill(buf, ' ');
        text_render(txt, buf, curs);
        curs_render(curs, buf);
        buf_print(buf);
        printf("x: %d, y: %d", curs->cursor_x, curs->cursor_y);
        printf("gx: %d, gy: %d", curs->global_cursor_x, curs->global_cursor_y);

        Key key = inp_read_key();
        if(key.ch == 'q'){
            break;
        } else if(key.code == KEY_RIGHT){
            curs_move(curs, txt, buf, RIGHT);
        } else if(key.code == KEY_LEFT){
            curs_move(curs, txt, buf, LEFT);
        } else if(key.code == KEY_UP){
            curs_move(curs, txt, buf, UP);
        } else if(key.code == KEY_DOWN){
            curs_move(curs, txt, buf, DOWN);
        }
    }

    curs_free(curs);
    text_free(txt);
    buf_free(buf);
}