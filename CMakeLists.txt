cmake_minimum_required(VERSION 3.17)
project(Random_Text_Generator C)

set(CMAKE_C_STANDARD 11)

add_executable(Random_Text_Generator main.c tdUtils/TemplateDictionary.h tdUtils/TemplateDictionary.c parserUtils/DataParse.c parserUtils/DataParse.h btfUtils/beautifier.c btfUtils/beautifier.h alphabetUtils/alphabet.c alphabetUtils/alphabet.h utilities.h namesUtils/nameChanger.c namesUtils/nameChanger.h)
