#ifndef DICIONARIO_OTIMIZACAO_H
#define DICIONARIO_OTIMIZACAO_H

#include <stdio.h>
#include <time.h>

/**
 * @brief Lógica central de compressão LZ78 com limite dinâmico e suporte para dicionários GIGANTES.
 */
void lz78_compress_logic_custom(FILE* input, FILE* output, unsigned int max_dict_limit);

/**
 * @brief Gera um nome único, executa a compressão e retorna o tempo gasto.
 */
double compress_and_save_custom(FILE* input, const char* folder, const char* filename, unsigned int max_dict_limit, char* out_filepath);

/**
 * @brief Testa vários tamanhos de dicionário, compara os rácios e os tempos.
 */
void Testar_Diferentes_Tamanhos_Dicionario(const char* comp_dir);

#endif // DICIONARIO_OTIMIZACAO_H