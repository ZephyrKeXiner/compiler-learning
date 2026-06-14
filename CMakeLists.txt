cmake_minimum_required(VERSION 3.20)

project(MyProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(clox src/main.cpp)

target_sources(clox PRIVATE
  src/include/chunk.cpp
  src/include/memory.cpp
  src/include/debug.cpp
  src/include/value.cpp
)

target_sources(clox PRIVATE
  src/include/common.h
  src/include/chunk.h
  src/include/memory.h
  src/include/debug.h
  src/include/value.h
)
