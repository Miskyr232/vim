#include "../include/input.h"

#include <stdio.h>
#include <unistd.h>

Key inp_read_key(){
    Key input = {KEY_UNKNOWN, 0};
    read(STDIN_FILENO, &input.ch, 1);

    // ctrl + letter
    if(input.ch >= 1 && input.ch <= 26) input.code = KEY_CTRL_A + input.ch - 1;

    if(input.ch == 27){
        char a, b;
        read(STDIN_FILENO, &a, 1);
        read(STDIN_FILENO, &b, 1);

        if(a == 91){
            if(b == 65) input.code = KEY_UP;
            if(b == 66) input.code = KEY_DOWN;
            if(b == 67) input.code = KEY_RIGHT;
            if(b == 68) input.code = KEY_LEFT;
            if(b == 72) input.code = KEY_HOME;
            if(b == 70) input.code = KEY_END;
            if(b == 51){ read(STDIN_FILENO, &input.ch, 1); input.code = KEY_DELETE; }  // \x1b[3~

            // Page Up/Down — \x1b[5~ и \x1b[6~
            if(b == 53){ read(STDIN_FILENO, &input.ch, 1); input.code = KEY_PAGE_UP; }
            if(b == 54){ read(STDIN_FILENO, &input.ch, 1); input.code = KEY_PAGE_DOWN; }

            // F1-F4 — \x1b[OP и тд
            if(b == 79){
                char c;
                read(STDIN_FILENO, &c, 1);
                if(c == 80) input.code = KEY_F1;
                if(c == 81) input.code = KEY_F2;
                if(c == 82) input.code = KEY_F3;
                if(c == 83) input.code = KEY_F4;
            }
        } else{
            input.code = KEY_ESC;
        }
        
    }

    if(input.ch == '\r')  input.code = KEY_ENTER;
    if(input.ch == 127)   input.code = KEY_BACKSPACE;
    if(input.ch == '\t')  input.code = KEY_TAB;

    return input;
}