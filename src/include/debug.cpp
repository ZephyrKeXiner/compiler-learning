#include <cstdio>
#include <string>

#include "debug.h"

static int simpleInstruction(const char* name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}

void disassembleChunk(Chunk* chunk, const char* name) {
  printf("=== %s ===\n", name);
  for (int offset = 0; offset < chunk->count;)
  {
    offset = disassembleInstruction(chunk, offset);
  }
}

int disassembleInstruction(Chunk* chunk, int offset) {
  printf("%04d ", offset);

  uint8_t instruction = chunk->code[offset];
  switch (instruction)
  {
  case OP_RETURN:
    return simpleInstruction("OP_RETURN", offset);

  case OP_CONSTANT: {
      offset = simpleInstruction("OP_CONSTANT", offset);
      printf("%04d ", offset);
      Value constant = chunk->constants.values[chunk->code[offset]];
      std::string s = std::to_string(constant);
      const char* p = s.c_str();
      return simpleInstruction(p, offset);
    }

  default:
    printf("Unknown opcode %d\n", instruction);
    return offset + 1;
  }
}