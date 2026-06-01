#include "../include/vector.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

vec* vec_new(int element_size_){
    vec* v = (vec*)malloc(sizeof(vec));
    v->element_size = element_size_;
    v->size = 0;
    v->capacity = 10;
    v->data = malloc(10 * element_size_);
    return v;
}

void vec_free(vec* v){
    free(v->data);
    free(v);
}

void vec_push_back(vec* v, void* value){
    if(v->size == v->capacity){
        int new_capasity = v->capacity * 2;
        v->data = realloc(v->data, v->element_size * new_capasity);
        v->capacity = new_capasity;
    }
    uint8_t* dst = (uint8_t*)v->data + v->size * v->element_size;
    memcpy(dst, value, v->element_size);
    v->size++;
}

void* vec_get(vec* v, int i){
    return (uint8_t*)v->data + i * v->element_size;
}