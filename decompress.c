//
// Created by clonic on 4/10/26.
//

#include "decompress.h"


void lz78_decompress_logic(FILE* input, FILE* output) {
    typedef struct {
        unsigned int prefix;
        char c;
    } DecompEntry;

    DecompEntry* dict = malloc(sizeof(DecompEntry) * MAX_DICT_SIZE);
    unsigned int dict_count = 1;
    unsigned short idx; // Change back to short

    
    while (fread(&idx, sizeof(unsigned short), 1, input) == 1) {
        int next_char = fgetc(input);
        if (next_char == EOF) break;

        // Reconstruct string using a stack
        static char temp_stack[MAX_DICT_SIZE]; // Large buffer for long patterns
        int top = 0;

        temp_stack[top++] = (char)next_char;
        unsigned int walk = idx;
        while (walk != 0) {
            temp_stack[top++] = dict[walk].c;
            walk = dict[walk].prefix;
        }

        for (int i = top - 1; i >= 0; i--) {
            if (temp_stack[i] != 0) {
                fputc(temp_stack[i], output);
            }
        }

        if (dict_count < MAX_DICT_SIZE) {
            dict[dict_count].prefix = idx;
            dict[dict_count].c = (char)next_char;
            dict_count++;
        }
    }
    free(dict);
}

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

void lz78_decompress_visual_debug(FILE* input, FILE* output) {
    printf("\n--- MODO VISUAL: Descomprimindo e Reconstruindo ---\n");
    printf("%-12s | %-12s | %-20s\n", "Token (Idx)", "Char Lido", "Frase Gerada");
    printf("----------------------------------------------------------------------\n");

    typedef struct {
        unsigned int prefix;
        char c;
    } DecompEntry;

    DecompEntry* dict = malloc(sizeof(DecompEntry) * MAX_DICT_SIZE);
    unsigned int dict_count = 1;
    unsigned short idx;

    while (fread(&idx, sizeof(unsigned short), 1, input) == 1) {
        int next_char = fgetc(input);
        if (next_char == EOF) break;

        // 1. Reconstrução usando a Pilha (Stack)
        static char temp_stack[MAX_DICT_SIZE];
        int top = 0;

        // Só adicionamos o caractere se não for o marcador de fim (0)
        if (next_char != 0) {
            temp_stack[top++] = (char)next_char;
        }

        unsigned int walk = idx;
        while (walk != 0) {
            temp_stack[top++] = dict[walk].c;
            walk = dict[walk].prefix;
        }

        // 2. Print visual formatado
        char char_desc[10];
        if (next_char == 0) strcpy(char_desc, "NULL/EOF");
        else if (next_char == '\n') strcpy(char_desc, "'\\n'");
        else sprintf(char_desc, "'%c'", (char)next_char);

        printf("[%5u]      | %-12s | ", idx, char_desc);

        // 3. Escrita no ficheiro e Print da frase reconstruída
        for (int i = top - 1; i >= 0; i--) {
            // Escreve no ficheiro real (apenas se não for nulo, por segurança)
            if (temp_stack[i] != 0) {
                fputc(temp_stack[i], output);
            }
            // Print para o terminal
            printf("%c", (temp_stack[i] == '\n' ? ' ' : temp_stack[i]));
        }
        printf("\n");

        // 4. ATUALIZAR DICIONÁRIO
        // Importante: Se o next_char for 0, o dicionário guarda o prefixo
        // mas o caractere fica 'vazio' para não corromper futuras frases.
        if (dict_count < MAX_DICT_SIZE) {
            dict[dict_count].prefix = idx;
            dict[dict_count].c = (char)next_char;
            dict_count++;
        }
    }

    // --- TABELA FINAL ---
    printf("\n--- DICIONARIO RECONSTRUIDO (Final) ---\n");
    printf("%-10s | %-10s | %-10s\n", "Indice", "Prefixo", "Char");
    for (unsigned int i = 1; i < dict_count && i <= 20; i++) {
        printf("%-10u | %-10u | '%c'\n", i, dict[i].prefix,
               (dict[i].c <= 32 ? ' ' : dict[i].c));
    }

    free(dict);
    printf("----------------------------------------------------------------------\n");
}

void decompress_and_save_debug(FILE* input, const char* folder, const char* filename) {
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
    lz78_decompress_visual_debug(input, output_file);

    fclose(output_file);
    printf("-> Descompressão concluída com sucesso em: %s\n", target_path);
}


