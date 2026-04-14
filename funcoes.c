#include "funcoes.h"

FILE* OpenFile(char* filename) {
    FILE* fptr = fopen(filename, "rb");
    if (fptr == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
    }
    return fptr;
}

long int findSize(char file_name[])
{
    // opening the file in read mode
    FILE* fp = fopen(file_name, "r");

    // checking if the file exist or not
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);

    // calculating the size of the file
    long int res = ftell(fp);

    // closing the file
    fclose(fp);

    return res;
}

float compressionRatio(char *uncompressed_path, char *compressed_path)
{
    FILE *uncomp = OpenFile(uncompressed_path);
    FILE *comp = OpenFile(compressed_path);

    // int uncomp_size = findSize();
}