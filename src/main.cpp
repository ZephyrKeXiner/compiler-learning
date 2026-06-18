#include <cstdio>
#include <cstdlib> 
#include <cstring>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "value.h"
#include "vm.h"

static void repl(VM& vm) {
  char line[1024];
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    vm.interpret(line);
  }
}

static char* readFile(const char* path) {
  FILE* file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(74);
  }

  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char* buffer = (char*)malloc(fileSize + 1);
  if (buffer == NULL) {
    fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
    exit(74);
  }
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  if (bytesRead < fileSize) {
    fprintf(stderr, "Could not read file \"%s\".\n", path);
    exit(74);
  }

  buffer[bytesRead] = '\0';

  fclose(file);
  return buffer;
}

static void runFile(const char* path, VM& vm) {
  char* source = readFile(path);
  InterpretResult result = vm.interpret(source);
  free(source); 

  if (result == INTERPRET_COMPILE_ERROR) exit(65);
  if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

int main (int argc, const char* argv []) {
  Chunk chunk;
  initChunk(&chunk);
  VM vm(&chunk);
  if (argc == 1) {
    repl(vm);
  } else if (argc == 2) {
    runFile(argv[1], vm);
  } else {
    fprintf(stderr, "Usage: clox [path]\n");
    exit(64);
  }

  writeConstant(&chunk, 1.2, 123);
  writeConstant(&chunk, 1.3, 123);
  writeConstant(&chunk, 2.4, 123);
  writeConstant(&chunk, 2.5, 123);
  writeChunk(&chunk, OP_ADD, 123);
  writeChunk(&chunk, OP_SUBTRACT, 123);
  writeChunk(&chunk, OP_MULTIPLY, 123);
  // writeConstant(&chunk, 352, 123);
  writeChunk(&chunk, OP_RETURN, 123);

  // disassembleChunk(&chunk, "test_chunk");

  freeChunk(&chunk);
  return 0;
}
