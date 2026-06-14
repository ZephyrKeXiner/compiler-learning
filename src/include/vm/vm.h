#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR,
} InterpretResult;

class VM
{
private:
  Chunk* chunk;
  uint8_t* ip;

  InterpretResult run();
  uint8_t readByte();
  Value readConstant();
  uint32_t readConstantLongIndex();
  Value readConstantLong();

public:
  explicit VM(Chunk* chunk);
  ~VM();
  InterpretResult interpret(Chunk* chunk);
};

#endif
