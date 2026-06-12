#pragma once

typedef enum{
    UP,
    DOWN,
    LEFT,
    RIGHT,
} Dirs;

typedef struct {
    int x, y; // начало
    int w, h; // размер
} Rect;