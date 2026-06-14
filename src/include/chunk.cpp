#include <cstdio>
#include <cstdlib>

#include "common.h"
#include "chunk.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = nullptr;
  chunk->lineCapacity = 0;
  chunk->lineCount = 0;
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
  }

  chunk->code[chunk->count] = byte;
  chunk->count++;

  if (chunk->lineCount > 0 &&
      chunk->lines[chunk->lineCount - 1].line == line) {
      chunk->lines[chunk->lineCount - 1].count++;
  } else 
  {
      if (chunk->lineCapacity < chunk->lineCount + 1) {
          int oldCapacity = chunk->lineCapacity;
          chunk->lineCapacity = growCapacity(oldCapacity);
          chunk->lines = growArray(chunk->lines, oldCapacity, chunk->lineCapacity);
      }

      chunk->lines[chunk->lineCount] = LineInfo{line, 1};
      chunk->lineCount++;
  }
}

int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

void freeChunk(Chunk* chunk) {
  freeArray<uint8_t>(chunk->code, chunk->capacity);
  freeArray<LineInfo>(chunk->lines, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

int getLine(const Chunk* chunk, int offset) {
  int currentOffset = 0;

  for (int i = 0; i < chunk->lineCount; i++)
  {
    LineInfo run = chunk->lines[i];
    if (offset < currentOffset + run.count)
    {
      return run.line;
    }
    currentOffset += run.count;
  }

  return -1;
}

void writeConstant(Chunk* chunk, Value value, int line) {
  constexpr int maxShortConstant = UINT8_MAX;
  constexpr int maxLongConstant = 0xffffff;

  if (chunk->constants.count > maxLongConstant) {
    fprintf(stderr, "Too many constants in one chunk.\n");
    exit(1);
  }

  int constant = addConstant(chunk, value);

  if (constant <= maxShortConstant) {
    writeChunk(chunk, OP_CONSTANT, line);
    writeChunk(chunk, static_cast<uint8_t>(constant), line);
    return;
  }

  writeChunk(chunk, OP_CONSTANT_LONG, line);
  writeChunk(chunk, static_cast<uint8_t>((constant >> 16) & 0xff), line);
  writeChunk(chunk, static_cast<uint8_t>((constant >> 8) & 0xff), line);
  writeChunk(chunk, static_cast<uint8_t>(constant & 0xff), line);
}
