#include <stdio.h>
#include "funcoes.h"
#include "TestesCode.h"

/* Lógica para portabilidade do mkdir entre Windows e Linux */
#ifdef _WIN32
    #include <direct.h>   // Biblioteca para Windows
    #define MKDIR(path) mkdir(path)
#else
    #include <sys/stat.h>  // Biblioteca para Linux/Unix
    #include <sys/types.h>
    #define MKDIR(path) mkdir(path, 0777)
#endif

/**
 * @mainpage LZ78 Compression Project
 *
 * ## Overview
 * This project implements the LZ78 algorithm for multimedia data compression.
 * It features a high-performance Hash Table implementation to ensure O(1)
 * average-time complexity during dictionary lookups.
 *
 * ## Key Modules
 * - **Compression:** Handles dictionary building and token generation.
 * - **Decompression:** Reconstructs original data using a stack-based walk.
 * - **Test Suite:** Includes automated testing for the Silesia Corpus.
 *
 * ## How to Navigate
 * Use the tabs above to explore the **Classes** (structs like HashEntry)
 * or **Files** to see the documented functions.
 */

/**
 * @brief Função principal que gere o fluxo de execução.
 * Permite escolher entre processar todo o corpus, ficheiros específicos ou testes manuais.
 * @return int Status de saída.
 */
int main(void) {
    // Nomes das pastas de saída
    const char* comp_dir = "silesia_compress";
    const char* rest_dir = "silesia_restored";

    // Cria as pastas usando a macro portátil
    MKDIR(comp_dir);
    MKDIR(rest_dir);

    // --- Opções de Execução ---

    // 1. Comprimir e descomprimir um ficheiro específico
    //Compress_Decompress_Especifico(comp_dir, rest_dir);

    // 2. Comprimir e descomprimir todos os ficheiros do Silesia Corpus
    // Compress_Decompress_ALL(comp_dir, rest_dir);

    // 3. Teste Manual com String (útil para o modo Visual Debug)
    // Teste_String_Manual(comp_dir, rest_dir);

    // 4. Teste de Otimização do Dicionário
    Teste_Otimizacao_Dicionario(comp_dir);
    return 0;
}