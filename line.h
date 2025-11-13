#ifndef clox_line_h
#define clox_line_h

#include "common.h"

typedef struct {
    int count;
    int capacity;
    int* line_number;
    int* line_count;
} LineArray;

void initLineArray(LineArray* lines);
void writeLineArray(LineArray* array, int line);
void freeLineArray(LineArray* array);
void growLineArray(LineArray* array);

#endif