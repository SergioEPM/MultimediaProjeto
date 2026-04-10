//
// Created by clonic on 4/10/26.
//

#include "decompress.h"
#include "compress.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///TODO logica decompress for lz78
void lz78_decompress_logic(FILE* input, FILE* output) {
    // Para descomprimir, precisamos guardar as strings do dicionário
    // Criamos um array de structs para reconstruir o caminho
    typedef struct {
        unsigned short prefix;
        char c;
    } DecompEntry;

    DecompEntry* dict = malloc(sizeof(DecompEntry) * MAX_DICT_SIZE);
    unsigned short dict_count = 1;

    unsigned short idx;
    int next_char;

    // LÊ: 2 bytes do índice e depois 1 byte do char
    while (fread(&idx, sizeof(unsigned short), 1, input) == 1) {
        next_char = fgetc(input);
        if (next_char == EOF) break;


        // Vamos usar um buffer temporário para inverter a string
        char temp_stack[MAX_DICT_SIZE];
        int top = 0;

        temp_stack[top++] = (char)next_char;
        unsigned short walk = idx;
        while (walk != 0) {
            temp_stack[top++] = dict[walk].c;
            walk = dict[walk].prefix;
        }

        // Imprime do fim para o início (ordem correta)
        for (int i = top - 1; i >= 0; i--) {
            fputc(temp_stack[i], output);
        }

        // Adiciona ao dicionário para as próximas consultas
        if (dict_count < MAX_DICT_SIZE) {
            dict[dict_count].prefix = idx;
            dict[dict_count].c = (char)next_char;
            dict_count++;
        }
    }
    free(dict);
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
