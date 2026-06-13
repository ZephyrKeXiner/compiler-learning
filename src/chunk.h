#ifndef clox_chunk_h 
#define clox_chunk_h

#include "common.h"
#include "memory.h"

typedef enum {
  OP_RETURN,
} OpCode;

typedef struct {
  int count;
  int capacity;
  uint8_t* code;
} Chunk;

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = nullptr;
}

void writeChunk(Chunk* chunk, uint8_t byte) {
  if (chunk->capacity < chunk->count + 1) 
  {
    int oldCapacity = chunk->capacity;
    int newCapacity = GROW_CAPACITY(oldCapacity);
    
  }
  chunk->count += 1;
  chunk->code[chunk->count] = byte;
}

#endif