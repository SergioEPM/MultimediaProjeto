cmake_minimum_required(VERSION 3.28)
project(MultimediaProjeto C)

set(CMAKE_C_STANDARD 17)

add_executable(MultimediaProjeto main.c
        compress.c
        compress.h
        decompress.c
        decompress.h
        funcoes.c
        funcoes.h
        TestesCode.c
        TestesCode.h)
