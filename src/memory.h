#ifndef clox_memory_h 
#define clox_memory_h 

#include "common.h" 

void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#define GROW_CAPACITY(capacity) \
  ((capacity < 8) ? 8 : capacity * 2)

#define GROW_ARRAY(type, pointer, oldSize, newSize) \
  (type*) reallocate(pointer, (sizeof(type)) * (oldSize), (sizeof(type)) * (newSize))

#define FREE_ARRAY(type, pointer, oldSize) \
  (type*) reallocate(pointer, (sizeof(type) * oldSize), 0)
  
#endif