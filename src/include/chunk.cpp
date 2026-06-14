#include "common.h"
#include "chunk.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = nullptr;
  chunk->lines = nullptr;
  initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) 
  {
    int oldCapacity = chunk->capacity;
    chunk->capacity = growCapacity(oldCapacity);
    chunk->code = growArray<uint8_t>(chunk->code, 
                    oldCapacity, chunk->capacity);
    chunk->lines = growArray<int>(chunk->lines,
                    oldCapacity, chunk->capacity);
  }
  chunk->code[chunk->count] = byte;
  chunk->lines[chunk->count] = line;
  chunk->count++;
}

int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

void freeChunk(Chunk* chunk) {
  freeArray<uint8_t>(chunk->code, chunk->capacity);
  freeArray<int>(chunk->lines, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}