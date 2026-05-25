//
// Created by clonic on 4/15/26.
//

#ifndef MULTIMEDIAPROJETO_TESTESCODE_H
#define MULTIMEDIAPROJETO_TESTESCODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "compress.h"
#include "funcoes.h"
#include "decompress.h"
#include "DicionarioOtimizacao.h"



/**
 * @file TestesCode.h
 * @brief Ficheiro header para os testes do projeto.
 */


/**
 * @brief Wrapper dos testes unitários do passo da compressão.
 * Abre um ficheiro fonte específico, corre a lógica da compressão, e 
 * certifica-se que o ficheiro é devidamente fechado.
 * @param in_path O caminho inteiro para o ficheiro original.
 * @param name O nome a ser usado para o output comprimido.
 * @param folder A diretoria destino para o ficheiro .lz78.
 */
void Teste_compress(const char* in_path, const char* name, const char* folder);

/**
 * @brief Wrapper dos testes unitários do passo da compressão.
 * Localiza o ficheiro .lz78 na pasta do input e restaura-a para a 
 * pasta output.
 * @param in_folder Onde o ficheiro comprimido está armazenado neste 
 * momento.
 * @param name O nome base do ficheiro (sem a extensão).
 * @param out_folder O destino para o ficheiro .txt restaurado.
 */
void Teste_decompress(const char* in_folder, const char* name, const char* out_folder);

/**
 * @brief Teste da função compressionEntropy()
 * @param file_path Caminho do ficheiro a calcular entropia
 */
void testeEntropia(const char *file_path);

/**
 * @brief Processador em lote para o Corpus da Silésia.
 * Itera manualmente pelos 12 ficheiros normais no dataset Silesia (dickens, 
 * mozilla, etc.), fazendo um ciclo compressão/descompressão inteiro em cada 
 * um.
 * @param comp_dir Diretoria para armazenar ficheiros comprimidos.
 * @param rest_dir Diretoria para armazenar ficheiros restaurados.
 */
void Compress_Decompress_ALL(const char* comp_dir, const char* rest_dir);

/**
 * @brief Ferramenta de benchmark para um ficheiro específico.
 * Comprime e descomprime o ficheiro "dickens" enquanto conta o tempo de 
 * execução com a função `clock()`. Imprime um relatório detalhado do tempo 
 * que cada passo demorou.
 * @param comp_dir Diretoria do output comprimido.
 * @param rest_dir Diretoria do output restaurado.
 */
void Compress_Decompress_Especifico(const char* comp_dir, const char* rest_dir);

/**
 * @brief Modo de debug interativo para testes em strings personalizadas.
 * Permite ao utilizador escrever uma frase na consola, escreve-a num ficheiro 
 * temporário e corre a versão "Visual Debug" da compressão e descompressão 
 * para mostrar exatamente como o dicionário LZ78 evolui.
 * @param comp_dir Diretoria para os dados comprimidos temporários.
 * @param rest_dir Diretoria para os dados restaurados temporários.
 */
void Teste_String_Manual(const char* comp_dir, const char* rest_dir);

// Nova função de teste para a otimização do dicionário
void Teste_Otimizacao_Dicionario(const char* comp_dir);

#endif //MULTIMEDIAPROJETO_TESTESCODE_H
