#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 1024

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

  Value stack[STACK_MAX];
  Value* stackTop = nullptr;

  InterpretResult run();
  uint8_t readByte();
  Value readConstant();
  uint32_t readConstantLongIndex();
  Value readConstantLong();

  void resetStack();
  void push(Value value);
  Value pop();
  
  template <typename Op>
  void binaryOp (Op op) {
    Value a = pop();
    Value b = pop();
    
    push(op(a, b));
  }

public:
  explicit VM(Chunk* chunk);
  ~VM();
  InterpretResult interpret();
};

#endif
