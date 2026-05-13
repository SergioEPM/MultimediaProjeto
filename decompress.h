//
// Created by clonic on 4/10/26.
//

#ifndef MULTIMEDIAPROJETO_DECOMPRESS_H
#define MULTIMEDIAPROJETO_DECOMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compress.h"

/**
 * @file decompress.h
 * @brief Ficheiro header que contém estruturas e protótipos para descompressão LZ78.
 */



/**
 * @brief Algoritmo de descompressão LZ78 principal a usar um dicionário baseado num array.
 * Reconstrói os dados originais lendo pares (índice, caractere). Utiliza um método baseado
 * numa stack para andar para trás no dicionário e imprimir sequências na ordem correta.
 * @param input Apontador para o ficheiro binário .lz78 comprimido.
 * @param output Apontador para o ficheiro destino para os dados restaurados.
 */
void lz78_decompress_logic(FILE* input, FILE* output);

/**
 * @brief Gere o boilerplate de entrada e saída da descompressão padrão.
 * Gera o caminho do ficheiro restaurado (ex.: adicionar "_restored.txt"), abre
 * o output stream e executa a lógica de descompressão.
 * @param input Pointer para o ficheiro fonte comprimido.
 * @param folder A string da diretoria destino (ex.: "silesia_restored").
 * @param filename O nome base do ficheiro a ser restaurado.
 */
void decompress_and_save(FILE* input, const char* folder, const char* filename);


/**
 * @brief Lógica de descompressão para análise de seguimento em tempo real
 * Imprime uma tabela para a consola passo a passo mostrando qual índice de 
 * tokens está a ser lido, o novo caractere adicionado e a string inteira a 
 * ser reconstruída a partir do dicionário.
 * @param input Pointer para o ficheiro binário comprimido.
 * @param output Pointer para o ficheiro destino restaurado.
 */
void lz78_decompress_visual_debug(FILE* input, FILE* output);


/**
 * @brief Wrapper para o modo de debug da descompressão visual.
 * Prepara o ficheiro de output e redireciona o processo para o tracer visual 
 * (lz78_decompress_visual_debug) para monitorizar a reconstrução do dicionário.
 * @param input Pointer para o ficheiro comprimido fonte.
 * @param folder A string da diretoria destino.
 * @param filename O nome base do ficheiro.
 */
void decompress_and_save_debug(FILE* input, const char* folder, const char* filename);

#endif //MULTIMEDIAPROJETO_DECOMPRESS_H
