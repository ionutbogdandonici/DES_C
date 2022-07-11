cmake_minimum_required(VERSION 3.22)
project(DES_Official C)

set(CMAKE_C_STANDARD 11)

add_executable(DES_Official main.c utility.c utility.h des.h des.c)
