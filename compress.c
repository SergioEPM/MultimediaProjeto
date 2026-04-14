#include "compress.h"

unsigned int hash_func(unsigned short prefix, char c) {
    return ((unsigned int)prefix << 8 | (unsigned char)c) % HASH_SIZE;
}

void lz78_compress_logic(FILE* input, FILE* output) {
    // calloc is important: it sets everything to 0
    HashEntry* hash_table = calloc(HASH_SIZE, sizeof(HashEntry));

    unsigned short dict_count = 1;
    unsigned short current_prefix = 0;
    int c;

    while ((c = fgetc(input)) != EOF) {
        unsigned int h = hash_func(current_prefix, (char)c);
        unsigned short found_index = 0;

        while (hash_table[h].dict_idx != 0) {
            if (hash_table[h].prefix_index == current_prefix && hash_table[h].character == (char)c) {
                found_index = hash_table[h].dict_idx;
                break;
            }
            h = (h + 1) % HASH_SIZE;
        }

        if (found_index != 0) {
            current_prefix = found_index;
        } else {
            // BACK TO 2 BYTES: Significant space saving!
            fwrite(&current_prefix, sizeof(unsigned short), 1, output);
            fputc(c, output);

            if (dict_count < MAX_DICT_SIZE) {
                hash_table[h].prefix_index = current_prefix;
                hash_table[h].character = (char)c;
                hash_table[h].dict_idx = dict_count;
                dict_count++;
            }
            current_prefix = 0;
        }
    }

    if (current_prefix != 0) {
        fwrite(&current_prefix, sizeof(unsigned short), 1, output);
        fputc(0, output);
    }

    free(hash_table);
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


void print_final_dictionary(HashEntry* hash_table) {
    printf("\n--- TABELA DO DICIONARIO FINAL (Top 20 entradas ou Preenchidas) ---\n");
    printf("%-10s | %-10s | %-10s | %-15s\n", "Indice", "Prefixo", "Caractere", "Representacao");
    printf("------------------------------------------------------------\n");

    // Criamos um array temporário para ordenar as entradas por dict_idx

    int count = 0;
    for (int i = 0; i < HASH_SIZE && count < 50; i++) {
        if (hash_table[i].dict_idx != 0) {
            char c = hash_table[i].character;
            char display_char[10];

            // Tratamento visual para caracteres especiais
            if (c == '\n') strcpy(display_char, "\\n");
            else if (c == '\t') strcpy(display_char, "\\t");
            else if (c == ' ') strcpy(display_char, "' '");
            else sprintf(display_char, "'%c'", c);

            printf("%-10u | %-10u | %-10s | (S%u + %s)\n",
                   hash_table[i].dict_idx,
                   hash_table[i].prefix_index,
                   display_char,
                   hash_table[i].prefix_index,
                   display_char);
            count++;
        }
    }
    printf("... (mostrando apenas as primeiras 50 entradas) ...\n");
    printf("------------------------------------------------------------\n\n");
}

void lz78_visual_debug(FILE* input, FILE* output) {
    printf("\n--- MODO VISUAL: Acompanhando o Dicionario ---\n");
    printf("%-20s | %-10s | %-20s\n", "Lendo (Pref, Char)", "Status", "Acao no Dicionario");
    printf("----------------------------------------------------------------------\n");

    HashEntry* hash_table = calloc(HASH_SIZE, sizeof(HashEntry));
    unsigned short dict_count = 1;
    unsigned short current_prefix = 0;
    int c;

    while ((c = fgetc(input)) != EOF) {
        char display_char = (c == '\n') ? ' ' : (char)c; // Troca newline por espaço para não quebrar o print
        unsigned int h = hash_func(current_prefix, (char)c);
        unsigned short found_index = 0;

        while (hash_table[h].dict_idx != 0) {
            if (hash_table[h].prefix_index == current_prefix && hash_table[h].character == (char)c) {
                found_index = hash_table[h].dict_idx;
                break;
            }
            h = (h + 1) % HASH_SIZE;
        }

        if (found_index != 0) {
            // O algoritmo já viu esta sequência!
            printf("(%3d, '%c')          | EXISTE     | Novo Prefixo sera: %d\n",
                   current_prefix, display_char, found_index);
            current_prefix = found_index;
        } else {
            // Sequência nova! Grava e cria entrada no dicionário
            printf("(%3d, '%c')          | NOVO       | Criando Indice %d -> Gravando no Ficheiro\n",
                   current_prefix, display_char, dict_count);

            fwrite(&current_prefix, sizeof(unsigned short), 1, output);
            fputc(c, output);

            if (dict_count < MAX_DICT_SIZE) {
                hash_table[h].prefix_index = current_prefix;
                hash_table[h].character = (char)c;
                hash_table[h].dict_idx = dict_count;
                dict_count++;
            }
            current_prefix = 0; // Reseta para começar nova sequência
        }
    }

    if (current_prefix != 0) {
        fwrite(&current_prefix, sizeof(unsigned short), 1, output);
        fputc(0, output);
    }

    print_final_dictionary(hash_table);
    free(hash_table);
    printf("----------------------------------------------------------------------\n");
}

void compress_and_save_logic_debug(FILE* input, const char* folder, const char* filename) {
    char target_path[256];

    // Build path: "silesia_output/dickens.lz78"
    snprintf(target_path, sizeof(target_path), "%s/%s.lz78", folder, filename);

    FILE* output_file = fopen(target_path, "wb"); // "wb" for Write Binary
    if (output_file == NULL) {
        perror("Failed to create output file");
        return;
    }

    // Call the LZ78 function
    lz78_visual_debug(input, output_file);

    fclose(output_file);
    printf("LZ78 compression finished: %s\n", target_path);
}


