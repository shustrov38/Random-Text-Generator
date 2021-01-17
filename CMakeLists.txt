cmake_minimum_required(VERSION 3.17)
project(Random_Text_Generator C)

set(CMAKE_C_STANDARD 11)

add_executable(Random_Text_Generator main.c db_utils/database.h db_utils/database.c)
