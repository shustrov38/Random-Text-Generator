cmake_minimum_required(VERSION 3.17)
project(Random_Text_Generator C)

set(CMAKE_C_STANDARD 11)

add_executable(Random_Text_Generator Race_Parse/main.c Race_Parse/DataParse.c Race_Parse/DataParse.h)