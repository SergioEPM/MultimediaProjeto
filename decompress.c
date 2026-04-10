//
// Created by clonic on 4/10/26.
//

#include "decompress.h"

#include <stdio.h>
#include <string.h>

///TODO logica decompress for lz78
void lz78_decompress_logic(FILE* input, FILE* output) {
    int c;
    printf("-> Iniciando Processamento de Descompressão...\n");

    // Lógica LZ78: Lê byte a byte do arquivo comprimido
    while ((c = fgetc(input)) != EOF) {

        /* MAKE DECOMPRESS

        */

        fputc(c, output);
    }
}

/// Função principal de descompressão
void decompress_and_save(FILE* input, const char* folder, const char* filename) {
    char target_path[256];

    // Constrói o caminho relativo: "silesia_restored/dickens_restored.txt"
    snprintf(target_path, sizeof(target_path), "%s/%s_restored.txt", folder, filename);

    // Abre o arquivo de saída em modo binário
    FILE* output_file = fopen(target_path, "wb");
    if (output_file == NULL) {
        fprintf(stderr, "Erro: Não foi possível criar o arquivo em %s\n", target_path);
        return;
    }

    // Executa a lógica de leitura e escrita
    lz78_decompress_logic(input, output_file);

    fclose(output_file);
    printf("-> Descompressão concluída com sucesso em: %s\n", target_path);
}
