#pragma once

#include <stdlib.h>

typedef struct{
    void* data;
    int size;
    int capacity;
    int element_size;
}vec;

vec* vec_new(int element_size_);
void vec_free(vec* v);
void vec_push_back(vec* v, void* value);
void* vec_get(vec* v, int i);
void vec_remove(vec *v, int i);