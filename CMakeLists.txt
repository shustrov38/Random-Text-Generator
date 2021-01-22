cmake_minimum_required(VERSION 3.17)
project(Random_Text_Generator C)

set(CMAKE_C_STANDARD 11)

add_executadd_executable(Random_Text_Generator main.c)
add_executable(utilities.h)
add_executable(tdUtils/TemplateDictionary.h tdUtils/TemplateDictionary.c)
add_executable(parserUtils/DataParse.c parserUtils/DataParse.h)
add_executable(btfUtils/beautifier.c btfUtils/beautifier.h)
