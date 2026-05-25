#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file compress.h
 * @brief Header que contém as estruturas necessárias para a compressão LZ78.
 */


/**
 * @def MAX_DICT_SIZE
 * @brief The maximum number of entries allowed in the LZ78 dictionary.
 * @brief Número máximo de entradas permitidas no dicionário LZ78.
 * Limitado a 65535 para caber num unsigned short (2 bytes).
 */
#define MAX_DICT_SIZE 65535

/**
 * @def HASH_SIZE
 * @brief Tamanho do array da Hash Table.
 * Utiliza um número primo (131071) muito maior que o tamanho do dicionário
 * para minimizar colisões e manter tempo de pesquisa O(1).
 */
#define HASH_SIZE 131071 // Prime number > MAX_DICT_SIZE


/**
 * @struct HashEntry
 * @brief Representa um único nó no dicionário da compressão.
 * Esta estrutura atribui uma sequência (prefixo + caracter) a um índice específico 
 * no dicionário.
 * Tamanho total: 5 bytes (mais padding potencial do compilador).
 * @var HashEntry::prefix_index
 * O índice do dicionário da sequência existente antes do caractere atual.
 * @var HashEntry::character
 * O novo caractere a ser adicionado ao prefixo para formar uma nova sequência.
 * @var HashEntry::dict_idx
 * O identificador único atribuído a esta nova sequência para referência futura.
 */
typedef struct {
    unsigned short prefix_index; // 2 bytes
    char character;              // 1 byte
    unsigned short dict_idx;     // 2 bytes
} HashEntry;

/**
 * @brief Função de hash simples para pesquisa no dicionário.
 * Combina o índice do prefixo atual e o próximo caractere para gerar uma hash key.
 * @param prefix O índice da sequência que já existe no dicionário.
 * @param c O próximo caractere no input stream.
 * @return unsigned int O índice hash calculado dentro de HASH_SIZE.
 */
unsigned int hash_func(unsigned short prefix, char c);



/**
 * @brief Algoritmo de compressão LZ78 principal, utilizando uma Hash Table.
 * Lê caracteres um por um, pesquisa pelo prefixo mais longo que existe no dicionário,
 * e escreve (prefix_index, next_char) pares no ficheiro de output.
 * @param input Pointer para o ficheiro fonte aberto.
 * @param output Pointer para o ficheiro .lz78 de destino aberto.
 */
void lz78_compress_logic(FILE* input, FILE* output);


/**
 * @brief Gere o boilerplate de entrada e saída da compressão padrão.
 * Gera o ficheiro no caminho desejado, abre o ficheiro binário, e começa a 
 * lógica da compressão.
 * @param input Pointer para o ficheiro fonte.
 * @param folder A string da diretoria destino.
 * @param filename O ficheiro original do ficheiro (vai ficar com .lz78)
 */
void compress_and_save_logic(FILE* input, const char* folder, const char* filename);



/**
 * @brief Auxiliar de debug para visualizar o estado da Hash Table.
 * Itera pela hash table e imprime as primeiras 50 entradas, mostrando como
 * as sequências são mapeadas nos índices do dicionário.
 * @param hash_table Apontador para o array HashEntry depois do calloc.
 */
void print_final_dictionary(HashEntry* hash_table);


/**
 * @brief Uma versão instrumentada do algoritmo LZ78 para propósitos educacionais.
 * Faz a compressão enquanto imprime todos os hits (EXISTE) e todos os misses (NOVO)
 * na consola.
 * @param input Apontador para o ficheiro fonte.
 * @param output Apontador para o ficheiro de output binário.
 */
void lz78_visual_debug(FILE* input, FILE* output);



/**
 * @brief Wrapper para o modo de debug visual.
 * O mesmo que a lógica normal, mas redireciona a tarefa da compressão para
 * lz78_visual_debug para rastreio em tempo real na consola.
 * @param input Apontador para o ficheiro fonte.
 * @param folder A string da diretoria destino.
 * @param filename O nome original do ficheiro.
 */
void compress_and_save_logic_debug(FILE* input, const char* folder, const char* filename);


#endif
