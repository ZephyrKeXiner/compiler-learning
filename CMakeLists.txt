cmake_minimum_required(VERSION 3.20)

project(MyProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(clox src/main.cpp)

target_include_directories(clox PRIVATE
  src/include
  src/include/vm
  src/include/compiler
  src/include/scanner
)

target_compile_definitions(clox PRIVATE DEBUG_TRACE_EXECUTION)

target_sources(clox PRIVATE
  src/include/chunk.cpp
  src/include/memory.cpp
  src/include/debug.cpp
  src/include/value.cpp
  src/include/vm/vm.cpp
  src/include/compiler/compiler.cpp
  src/include/scanner/scanner.cpp
)

target_sources(clox PRIVATE
  src/include/common.h
  src/include/chunk.h
  src/include/memory.h
  src/include/debug.h
  src/include/value.h
  src/include/vm/vm.h
  src/include/compiler/compiler.h
  src/include/scanner/scanner.h
)
