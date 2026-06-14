#include "include/common.h"
#include "include/chunk.h"
#include "include/debug.h"
#include "include/value.h"

int main (int argc, const char* argv []) {
  Chunk chunk;
  initChunk(&chunk);
  writeConstant(&chunk, 1.2, 123);
  writeChunk(&chunk, OP_RETURN, 123);

  disassembleChunk(&chunk, "test_chunk");

  freeChunk(&chunk);
  return 0;
}
