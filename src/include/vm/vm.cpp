#include "common.h"
#include "vm.h"
#include "debug.h"
#include <cstdio>

VM::VM(Chunk* chunk)
    : chunk(chunk) {
}

VM::~VM() {

}

InterpretResult VM::interpret(Chunk* chunk) {
  VM::ip = VM::chunk->code;
  return VM::run();
}

uint8_t VM::readByte() {
  return *ip++;
}

Value VM::readConstant() {
  return chunk->constants.values[readByte()];
}

uint32_t VM::readConstantLongIndex() {
  int b1 = readByte();
  int b2 = readByte();
  int b3 = readByte();

  return (b1 << 16) | (b2 << 8) | b3;
}

Value VM::readConstantLong() {
  int constant = readConstantLongIndex();
  return chunk->constants.values[constant];
}

InterpretResult VM::run() {
  for (;;)
  {
    #ifdef DEBUG_TRACE_EXECUTION
      disassembleInstruction(chunk, static_cast<int>(ip - chunk->code));
    #endif

    uint8_t instruction;
    switch (instruction = VM::readByte())
    {
    case OP_RETURN:
      return INTERPRET_OK;
    
    case OP_CONSTANT: {
      Value constant = readConstant();
      printValue(constant);
      printf("\n");
      break;
    }

    case OP_CONSTANT_LONG: {
      Value constant = readConstantLong();
      printValue(constant);
      break;
    }

    default:
      break;
    }
  }
}
