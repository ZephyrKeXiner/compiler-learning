#include "common.h"
#include "chunk.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = nullptr;
  initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte) {
  if (chunk->capacity < chunk->count + 1) 
  {
    int oldCapacity = chunk->capacity;
    chunk->capacity = growCapacity(oldCapacity);
    chunk->code = growArray<uint8_t>(chunk->code, 
                    oldCapacity, chunk->capacity);
  }
  chunk->code[chunk->count] = byte;
  chunk->count++;
}

int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

void freeChunk(Chunk* chunk) {
  freeArray<uint8_t>(chunk->code, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}