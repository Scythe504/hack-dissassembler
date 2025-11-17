cmake_minimum_required(VERSION 3.16)
project(hack_disassembler)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(hdasm
  src/main.cpp
  src/code.cpp
)