cmake_minimum_required(VERSION 3.20)

project(MyProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(clox src/main.cpp)

target_sources(clox PRIVATE
  src/chunk.cpp
  src/memory.cpp
)

target_sources(clox PRIVATE
  src/common.h
  src/chunk.h
  src/memory.h
)
