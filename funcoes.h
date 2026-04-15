#ifndef MULTIMEDIAPROJETO_FUNCOES_H
#define MULTIMEDIAPROJETO_FUNCOES_H

#include <stdio.h>

/**
 * @brief Helper function to safely open files.
 * Provides a centralized way to open files in binary read mode with
 * built-in error reporting to stderr.
 * * @param filename The path/name of the file to open.
 * @return FILE* A pointer to the opened file, or NULL if it failed.
 */
FILE* OpenFile(char* filename);

long int findSize(const char file_name[]);
float compressionRatio(const char *uncompressed_path, const char *compressed_path);

#endif //MULTIMEDIAPROJETO_DECOMPRESS_H