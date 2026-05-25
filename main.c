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
 * ## Resumo
 * Este projeto implementa o algoritmo LZ78 para compressão de dados multimédia.
 * Implementa uma hash table para assegurar complexidade de tempo média O(1) 
 * durante as pesquisas no dicionário
 *
 * ## Módulos Chave
 * - **Compression:** Gere a construção de dicionários e a geração de tokens.
 * - **Decompression:** Reconstrói os dados originais utilizando uma pesquisa baseada em pilha.
 * - **Conjunto de Testes** Inclui testes automatizados para o Silesia Corpus
 *
 * ## Como Navegar
 * Utilize as tabs acima para explorar as **Classes** (structs como HashEntry)
 * ou **Files** para ver as funções documentadas
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
    const char* p_dickens = "silesia/dickens";

    // Cria as pastas usando a macro portátil
    MKDIR(comp_dir);
    MKDIR(rest_dir);
    MKDIR(p_dickens);

    // --- Opções de Execução ---

    // 1. Comprimir e descomprimir um ficheiro específico
    // Compress_Decompress_Especifico(comp_dir, rest_dir);

    // 2. Comprimir e descomprimir todos os ficheiros do Silesia Corpus
    // Compress_Decompress_ALL(comp_dir, rest_dir);

    // 3. Teste Manual com String (útil para o modo Visual Debug)
    Teste_String_Manual(comp_dir, rest_dir);

    // testeEntropia(p_dickens);

    // 4. Teste de Otimização do Dicionário
    Teste_Otimizacao_Dicionario(comp_dir);
    return 0;
}