#ifndef MULTIMEDIAPROJETO_FUNCOES_H
#define MULTIMEDIAPROJETO_FUNCOES_H

#include <math.h>
#include <stdio.h>

/**
 * @brief Função ajudante para abrir ficheiros de maneira segura.
 * Oferece uma forma centralizada de abrir ficheiros em modo leitura 
 * binária com relatórios de erros para o stderr integrados.
 * @param filename O nome/caminho do ficheiro a abrir.
 * @return FILE* Um pointer para o ficheiro aberto, ou NULL se falhar.
 */
FILE* OpenFile(char* filename);

/**
 * Retorna o tamanho do ficheiro passado no argumento
 * @param file_name O caminho do ficheiro
 */
long int findSize(const char file_name[]);

/**
 * @brief Retorna o rácio de compressão do processo de compressão feito
 * Divide o tamanho do ficheiro antes da compressão e o tamanho do ficheiro 
 * depois da compressão.
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