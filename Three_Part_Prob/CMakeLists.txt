cmake_minimum_required(VERSION 3.21.1)
project(Three_Part_Prob)

set(CMAKE_CXX_STANDARD 17)

add_executable(Three_Part_Prob main.cpp tp_args.hpp methods.h methods.cpp)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")