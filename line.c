#include<stdio.h>

#include "memory.h"
#include "line.h"

void initLineArray(LineArray* array) {
    array->capacity = 0;
    array->count = 0;
    array->line_number = NULL;
    array->line_count = NULL;
}

void freeLineArray(LineArray* array) {
    FREE_ARRAY(int, array->line_number, array->capacity);
    FREE_ARRAY(int, array->line_count, array->capacity);
    initLineArray(array);
}

void growLineArray(LineArray* array) {
    int oldCapacity = array->capacity;
    array->capacity = GROW_CAPACITY(oldCapacity);
    array->line_number = GROW_ARRAY(int*, array->line_number, oldCapacity, array->capacity);
    array->line_count = GROW_ARRAY(int*, array->line_count, oldCapacity, array->capacity);
}

void writeLineArray(LineArray* array, int line) {
    if(array->capacity == 0) {
        growLineArray(array);
        array->line_number[array->count] = line;
        array->line_count[array->count]++;
        array->count++;
    } else {
        if(array->line_number[array->count-1] == line) {
            array->line_count[array->count-1]++;
        } else {
            if(array->capacity < array->count + 1) growLineArray(&array);
            array->line_number[array->count] = line;
            array->line_count[array->count] = 1;
            array->count++;
        }
    }
}

