#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>

// 65535 é o valor máximo de um unsigned short (2 bytes)
#define MAX_DICT_SIZE 65535

typedef struct {
    unsigned short prefix_index; // 2 bytes
    char character;              // 1 byte
} DictEntry;

void compress_and_save_logic(FILE* input, const char* folder, const char* filename);
#endif
