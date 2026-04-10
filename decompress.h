//
// Created by clonic on 4/10/26.
//

#ifndef MULTIMEDIAPROJETO_DECOMPRESS_H
#define MULTIMEDIAPROJETO_DECOMPRESS_H
#include <stdio.h>

// Funções de Compressão (em compress.c)
void compress_and_save_logic(FILE* input, const char* folder, const char* filename);

// Funções de Descompressão (em decompress.c)
void decompress_and_save(FILE* input, const char* folder, const char* filename);
#endif //MULTIMEDIAPROJETO_DECOMPRESS_H
