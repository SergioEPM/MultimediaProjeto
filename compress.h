#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_DICT_SIZE 65535
#define HASH_SIZE 131071 // Prime number > MAX_DICT_SIZE

typedef struct {
    unsigned short prefix_index; // 2 bytes
    char character;              // 1 byte
    unsigned short dict_idx;     // 2 bytes
} HashEntry;


void compress_and_save_logic(FILE* input, const char* folder, const char* filename);
#endif
