#include "common.h"
#include "vm.h"
#include "debug.h"
#include "compiler.h"

#include <cstdio>

VM::VM(Chunk* chunk)
    : chunk(chunk) {
    VM::resetStack();
}

VM::~VM() {

}

InterpretResult VM::interpret(const char* source) {
  compile(source);
  return INTERPRET_OK;
}

uint8_t VM::readByte() {
  return *ip++;
}

Value VM::readConstant() {
  return chunk->constants.values[readByte()];
}

void VM::resetStack() {
  stackTop = stack;
}

void VM::push(Value value) {
  *stackTop = value;
  stackTop++;
}

Value VM::pop() {
  return *(--stackTop);
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
      printf("          ");
      for (Value* slot = stack; slot < stackTop; slot++) {
        printf("[ ");
        printValue(*slot);
        printf(" ]");
      }
      printf("\n");
      disassembleInstruction(chunk, static_cast<int>(ip - chunk->code));
    #endif

    uint8_t instruction;
    switch (instruction = readByte())
    {    
    case OP_CONSTANT: {
      Value constant = readConstant();
      push(constant);
      break;
    }

    case OP_CONSTANT_LONG: {
      Value constant = readConstantLong();
      push(constant);
      break;
    }

    case OP_NEGATE: 
      push(-pop());
      break;

    case OP_ADD:
      binaryOp([] (Value a, Value b) { return a + b; });
      break;

    case OP_SUBTRACT:
      binaryOp([] (Value a, Value b) { return a - b; });
      break;

    case OP_MULTIPLY:
      binaryOp([] (Value a, Value b) { return a * b; });
      break;
    
    case OP_DIVIDE:
      binaryOp([] (Value a, Value b) { return a / b; });
      break;
    
    case OP_RETURN:
      printValue(pop());
      printf("\n");
      return INTERPRET_OK;

    default:
      break;
    }
  }
}
