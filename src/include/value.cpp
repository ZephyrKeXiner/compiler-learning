#include <cstdio>

#include "memory.h"
#include "value.h"

void initValueArray(ValueArray* valueArray) {
  valueArray->capacity = 0;
  valueArray->count = 0;
  valueArray->values = nullptr;
}

void writeValueArray(ValueArray* valueArray, Value value) {
  if (valueArray->capacity < valueArray->count + 1)
  {
    int oldCapacity = valueArray->capacity;
    valueArray->capacity = growCapacity(oldCapacity);
    valueArray->values = growArray<Value>(valueArray->values, 
                            oldCapacity, valueArray->capacity);
  }
  valueArray->values[valueArray->count] = value;
  valueArray->count++;
}

void freeValueArray(ValueArray* valueArray) {
  freeArray<Value>(valueArray->values, valueArray->capacity);
  initValueArray(valueArray);
}