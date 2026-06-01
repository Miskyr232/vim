#include "../include/buffer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Buffer* buf_create(int w, int h){
    Buffer* buf = malloc(sizeof(Buffer));
    buf->data = malloc(w * h * sizeof(char));
    buf->H = h;
    buf->W = w;
    return buf;
}

void buf_free(Buffer *buf){
    free(buf->data);
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
    int d = 1;
    for(int i = 0; i < buf->H * buf->W; i++){
        printf("%c", buf->data[i]);
        if(d == buf->W){
            d = 0;
            printf("\n");
        }
        d++;
    }
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