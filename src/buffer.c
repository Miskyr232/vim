#include "../include/buffer.h"
#include "../include/settings.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static char* fg_table[] = {
    "\033[0m",   //normal
    "\033[7m",   //invert
    "\033[31m",  //red
    "\033[32m",  //green
    "\033[34m",  //blue
    "\033[33m",  //yellow
};

static char* bg_table[] = {
    "",          // normal (нет фона)
    "",          // invert
    "\033[41m",  // red
    "\033[42m",  // green
    "\033[44m",  // blue
    "\033[43m",  // yellow
};

Buffer* buf_create(int w, int h){
    Buffer* buf = malloc(sizeof(Buffer));
    buf->data = malloc(w * h * sizeof(char));
    buf->fg = malloc(w * h * sizeof(Color));
    buf->bg = malloc(w * h * sizeof(Color));
    buf->H = h;
    buf->W = w;
    return buf;
}

void buf_free(Buffer *buf){
    free(buf->data);
    free(buf->fg);
    free(buf->bg);
    free(buf);
}

void buf_set(Buffer* buf, int x, int y, char value){
    if(x < 0 || x >= buf->W || y < 0 || y >= buf->H){
        return;
    }
    buf->data[y * buf->W + x] = value;
}

char buf_get(Buffer *buf, int x, int y){
    if(x < 0 || x >= buf->W || y < 0 || y >= buf->H){
        return ' ';
    }
    return buf->data[y * buf->W + x];
}

void buf_print(Buffer* buf){
    int out_size = buf->H * buf->W * 20 + buf->H; // с запасом
    char *out = malloc(out_size);
    int pos = 0;
    int d = 1;
    
    for(int i = 0; i < buf->H * buf->W; i++){
        char ch = buf->data[i];
        const char *fg = fg_table[buf->fg[i]];
        const char *bg = bg_table[buf->bg[i]];
        memcpy(&out[pos], fg, strlen(fg)); pos += strlen(fg);
        memcpy(&out[pos], bg, strlen(bg)); pos += strlen(bg);
        // дальше как раньше
        if(ch == '\t'){
            for(int _ = 0; _ < g_settings.tab_size; _++){
                out[pos++] = ' ';
                if(d == buf->W){
                    if(i < buf->H * buf->W - 1) out[pos++] = '\n'; // не последняя строка
                    d = 1;
                } else d++;
            }
        } else {
            out[pos++] = ch;
            if(d == buf->W){
                if(i < buf->H * buf->W - 1) out[pos++] = '\n'; // не последняя строка
                d = 1;
            } else d++;
        }
    }    
    fwrite(out, 1, pos, stdout);
    fflush(stdout);
    free(out);
}

void buf_fill(Buffer *buf, char value){
    for(int i = 0; i < buf->H * buf->W; i++){
        buf->data[i] = value;
    }
}

void buf_set_string(Buffer* buf, int x, int y, const char *str){
    if(((y * buf->W + x) > (buf->W * buf->H)) || ((strlen(str) + (y * buf->W + x)) > (buf->W * buf->H))){
        return;
    }
    for(int i = 0; i < strlen(str); i++){
        buf_set(buf, x + i, y, str[i]);
    }
}

void buf_fill_fg(Buffer *buf, Color col){
    for(int i = 0; i < buf->H * buf->W; i++){
        buf->fg[i] = col;
    }
}

void buf_set_fg(Buffer *buf, int x, int y, Color col){
    if(x < 0 || x >= buf->W || y < 0 || y >= buf->H){
        return;
    }
    buf->fg[y * buf->W + x] = col;
}

void buf_fill_bg(Buffer *buf, Color col){
    for(int i = 0; i < buf->H * buf->W; i++){
        buf->bg[i] = col;
    }
}

void buf_set_bg(Buffer *buf, int x, int y, Color col){
    if(x < 0 || x >= buf->W || y < 0 || y >= buf->H){
        return;
    }
    buf->bg[y * buf->W + x] = col;
}