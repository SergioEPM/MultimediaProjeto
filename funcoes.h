#ifndef MULTIMEDIAPROJETO_FUNCOES_H
#define MULTIMEDIAPROJETO_FUNCOES_H

#include <math.h>
#include <stdio.h>

/**
 * @brief Helper function to safely open files.
 * Provides a centralized way to open files in binary read mode with
 * built-in error reporting to stderr.
 * @param filename The path/name of the file to open.
 * @return FILE* A pointer to the opened file, or NULL if it failed.
 */
FILE* OpenFile(char* filename);

/**
 * Retorna o tamanho do ficheiro passado no argumento
 * @param file_name O caminho do ficheiro
 */
long int findSize(const char file_name[]);

/**
 * @brief Retorna o rácio de compressão do processo de compressão feito
 * Divide o tamanho do ficheiro antes da compressão e o tamanho do ficheiro depois da compressão
 * @param uncompressed_path Caminho do ficheiro intacto
 * @param compressed_path Caminho do ficheiro comprimido
 */
float compressionRatio(const char *uncompressed_path, const char *compressed_path);

/**
 * @brief Retorna a entropia do ficheiro
 * Implementa a fórmula do cálculo da entropia onde a probabilidade 
 * de um símbolo aparecer é multiplicada pelo logaritmo de base 2 
 * dessa probabilidade, e esse valor será somado à soma dos resultados 
 * dos símbolos seguintes. Por fim o sinal do resultado será trocado.
 * @param file_path Caminho do ficheiro a calcular
 */
float compressionEntropy(const char *file_path);

#endif //MULTIMEDIAPROJETO_DECOMPRESS_H