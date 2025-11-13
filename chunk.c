#include <stdlib.h>

#include "chunk.h"
#include "line.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    initLineArray(&chunk->lines);
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    freeLineArray(&chunk->lines);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
    writeLineArray(&chunk->lines, line);
    if(chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }
    chunk->code[chunk->count] = byte;
    chunk->count++;
}

int addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

void writeConstant(Chunk* chunk, Value value, int line) {
    int constant = addConstant(chunk, value);
    if(constant <= 0xFF) {
        writeChunk(chunk, OP_CONSTANT, line);
        writeChunk(chunk, constant, line);
    } else {
        writeChunk(chunk, OP_CONSTANT_LONG, line);
        writeChunk(chunk, (uint8_t)((constant >> 16) & 0xFF), line);
        writeChunk(chunk, (uint8_t)((constant >> 8) & 0xFF), line);
        writeChunk(chunk, (uint8_t)(constant & 0xFF), line);
    }
}