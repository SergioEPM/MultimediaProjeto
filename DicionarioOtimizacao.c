#include "DicionarioOtimizacao.h"
#include "compress.h"
#include "funcoes.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura customizada para esta otimização (Usa unsigned int para suportar > 65535)
typedef struct {
    unsigned int prefix_index; // 4 bytes
    char character;            // 1 byte
    unsigned int dict_idx;     // 4 bytes
} HashEntry_Otimizacao;

// Função Hash ajustada para esta tabela
unsigned int hash_func_otimizada(unsigned int prefix, char c, unsigned int hash_size) {
    return ((prefix << 8) | (unsigned char)c) % hash_size;
}

void lz78_compress_logic_custom(FILE* input, FILE* output, unsigned int max_dict_limit) {
    // Para dicionários muito grandes, a Hash Table tem de ser maior para evitar colisões
    unsigned int hash_size = max_dict_limit * 2 + 1;

    HashEntry_Otimizacao* hash_table = calloc(hash_size, sizeof(HashEntry_Otimizacao));
    if (hash_table == NULL) {
        fprintf(stderr, "Erro de memoria ao alocar a tabela de hash para o limite %u\n", max_dict_limit);
        return;
    }

    unsigned int dict_count = 1;
    unsigned int current_prefix = 0;
    int c;

    // Se o limite for até 65535, escrevemos 2 bytes. Se for maior, 4 bytes!
    size_t bytes_to_write = (max_dict_limit <= 65535) ? 2 : 4;

    while ((c = fgetc(input)) != EOF) {
        unsigned int h = hash_func_otimizada(current_prefix, (char)c, hash_size);
        unsigned int found_index = 0;

        while (hash_table[h].dict_idx != 0) {
            if (hash_table[h].prefix_index == current_prefix && hash_table[h].character == (char)c) {
                found_index = hash_table[h].dict_idx;
                break;
            }
            h = (h + 1) % hash_size;
        }

        if (found_index != 0) {
            current_prefix = found_index;
        } else {
            fwrite(&current_prefix, bytes_to_write, 1, output);
            fputc(c, output);

            if (dict_count < max_dict_limit) {
                hash_table[h].prefix_index = current_prefix;
                hash_table[h].character = (char)c;
                hash_table[h].dict_idx = dict_count;
                dict_count++;
            }
            current_prefix = 0;
        }
    }

    if (current_prefix != 0) {
        fwrite(&current_prefix, bytes_to_write, 1, output);
        fputc(0, output);
    }

    free(hash_table);
}

double compress_and_save_custom(FILE* input, const char* folder, const char* filename, unsigned int max_dict_limit, char* out_filepath) {
    snprintf(out_filepath, 256, "%s/%s_dict%u.lz78", folder, filename, max_dict_limit);

    FILE* output_file = fopen(out_filepath, "wb");
    if (output_file == NULL) {
        perror("Falha ao criar o ficheiro de output");
        return 0.0;
    }

    clock_t inicio = clock();
    lz78_compress_logic_custom(input, output_file, max_dict_limit);
    clock_t fim = clock();

    fclose(output_file);

    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

void Testar_Diferentes_Tamanhos_Dicionario(const char* comp_dir) {
    // ATENÇÃO: Confirma se "silesia/dickens" existe na tua pasta!
    const char* original_filepath = "silesia/dickens";
    const char* filename = "dickens";

    unsigned int tamanhos_a_testar[] = {4096, 32768, 65535, 300000, 1000000};
    int num_testes = sizeof(tamanhos_a_testar) / sizeof(tamanhos_a_testar[0]);

    float melhor_racio = 0.0;
    unsigned int melhor_tamanho = 0;
    char melhor_ficheiro[256] = "";

    printf("\n=========================================================================\n");
    printf(" ANALISE: TAMANHO DO DICIONARIO vs TEMPO vs RACIO (Ficheiro: %s)\n", filename);
    printf("=========================================================================\n");
    printf("%-8s | %-12s | %-12s | %-10s | %-15s\n", "Teste", "Tamanho Dto", "Tempo (seg)", "Racio", "Ficheiro");
    printf("-------------------------------------------------------------------------\n");

    for (int i = 0; i < num_testes; i++) {
        unsigned int limite_atual = tamanhos_a_testar[i];

        FILE* input = fopen(original_filepath, "rb");
        if (input == NULL) {
            fprintf(stderr, "Erro ao abrir o ficheiro original: %s\n", original_filepath);
            fprintf(stderr, "DICA: Verifica se a pasta 'silesia' esta no local certo!\n");
            return;
        }

        char out_filepath[256];
        double tempo_gasto = compress_and_save_custom(input, comp_dir, filename, limite_atual, out_filepath);
        fclose(input);

        float racio = compressionRatio(original_filepath, out_filepath);

        printf("Teste %-2d | %-12u | %-12.4f | %-10.4f | %s\n",
               i+1, limite_atual, tempo_gasto, racio, out_filepath);

        if (racio > melhor_racio) {
            melhor_racio = racio;
            melhor_tamanho = limite_atual;
            strcpy(melhor_ficheiro, out_filepath);
        }
    }

    printf("-------------------------------------------------------------------------\n");
    printf(">>> VENCEDOR DO RACIO: %-10.4f (Tamanho do Dicionario: %u)\n", melhor_racio, melhor_tamanho);
    printf("=========================================================================\n\n");
}