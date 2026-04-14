#ifndef MULTIMEDIAPROJETO_FUNCOES_H
#define MULTIMEDIAPROJETO_FUNCOES_H

#include <stdio.h>

FILE* OpenFile(char* filename);
long int findSize(char file_name[]);
float compressionRatio(char *uncompressed_path, char *compressed_path);

#endif //MULTIMEDIAPROJETO_DECOMPRESS_H