#include "compress.h"
#include <stdlib.h>



void lz78_compress_logic(FILE* input, FILE* output) {
    printf("Executando LZ78 (16-bit) em ficheiro grande...\n");

    // Alocamos o dicionário no "Heap" para não dar estouro de pilha (Stack Overflow)
    DictEntry* dictionary = malloc(sizeof(DictEntry) * MAX_DICT_SIZE);
    if (!dictionary) {
        fprintf(stderr, "Erro de memória!\n");
        return;
    }

    unsigned short dict_count = 1;
    unsigned short current_prefix = 0;
    int c;

    int bytes_processados = 0;
    while ((c = fgetc(input)) != EOF) {
        int found_index = -1;
        ///TEMP
        bytes_processados++;
        if (bytes_processados % 100000 == 0) { // A cada 100KB
            printf("Processando... %d KB\n", bytes_processados / 1024);
        }
        /////

        // Procura no dicionário
        for (int i = 1; i < dict_count; i++) {
            if (dictionary[i].prefix_index == current_prefix && dictionary[i].character == (char)c) {
                found_index = i;
                break;
            }
        }

        if (found_index != -1) {
            current_prefix = (unsigned short)found_index;
        } else {
            // GRAVAÇÃO OTIMIZADA: Escreve 2 bytes do índice + 1 byte do char
            fwrite(&current_prefix, sizeof(unsigned short), 1, output);
            fputc(c, output);

            // Atualiza dicionário
            if (dict_count < MAX_DICT_SIZE) {
                dictionary[dict_count].prefix_index = current_prefix;
                dictionary[dict_count].character = (char)c;
                dict_count++;
            }

            current_prefix = 0;
        }
    }

    // Grava o resto se o ficheiro acabar
    if (current_prefix != 0) {
        fwrite(&current_prefix, sizeof(unsigned short), 1, output);
        fputc(0, output);
    }

    free(dictionary); // Libertar a memória alocada
    printf("Dicionário finalizou com %d entradas.\n", dict_count);
}

void compress_and_save_logic(FILE* input, const char* folder, const char* filename) {
    char target_path[256];

    // Build path: "silesia_output/dickens.lz78"
    snprintf(target_path, sizeof(target_path), "%s/%s.lz78", folder, filename);

    FILE* output_file = fopen(target_path, "wb"); // "wb" for Write Binary
    if (output_file == NULL) {
        perror("Failed to create output file");
        return;
    }

    // Call the LZ78 function
    lz78_compress_logic(input, output_file);

    fclose(output_file);
    printf("LZ78 compression finished: %s\n", target_path);
}