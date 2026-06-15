#include <cstdio>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "value.h"
#include "vm.h"

int main (int argc, const char* argv []) {
  Chunk chunk;
  initChunk(&chunk);
  VM vm(&chunk);

  writeConstant(&chunk, 1.2, 123);
  writeConstant(&chunk, 1.3, 123);
  writeConstant(&chunk, 2.4, 123);
  writeConstant(&chunk, 2.5, 123);
  writeChunk(&chunk, OP_ADD, 123);
  writeChunk(&chunk, OP_SUBTRACT, 123);
  writeChunk(&chunk, OP_MULTIPLY, 123);
  // writeConstant(&chunk, 352, 123);
  writeChunk(&chunk, OP_RETURN, 123);

  vm.interpret();
  // disassembleChunk(&chunk, "test_chunk");

  freeChunk(&chunk);
  return 0;
}
