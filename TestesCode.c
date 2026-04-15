//
// Created by clonic on 4/15/26.
//

#include "TestesCode.h"
#include <sys/stat.h>
#include <time.h>
#include "compress.h"
#include "decompress.h"



FILE* OpenFile(char* filename) {
    FILE* fptr = fopen(filename, "rb");
    if (fptr == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
    }
    return fptr;
}

void Teste_compress(const char* in_path, const char* name, const char* folder) {
    FILE* f_in = OpenFile((char*)in_path);
    if (f_in != NULL) {
        compress_and_save_logic(f_in, folder, name);
        fclose(f_in);
    }
}

void Teste_decompress(const char* in_folder, const char* name, const char* out_folder) {
    char compressed_path[256];
    snprintf(compressed_path, sizeof(compressed_path), "%s/%s.lz78", in_folder, name);

    FILE* f_comp = OpenFile(compressed_path);
    if (f_comp != NULL) {
        decompress_and_save(f_comp, out_folder, name);
        fclose(f_comp);
    }
}

void Compress_Decompress_ALL(const char* comp_dir, const char* rest_dir) {
    // --- MANUAL PATHS FOR THE ENTIRE SILESIA CORPUS ---

    const char* p_dickens = "silesia/dickens";
    Teste_compress(p_dickens, "dickens", comp_dir);
    Teste_decompress(comp_dir, "dickens", rest_dir);

    const char* p_mozilla = "silesia/mozilla";
    Teste_compress(p_mozilla, "mozilla", comp_dir);
    Teste_decompress(comp_dir, "mozilla", rest_dir);

    const char* p_mr = "silesia/mr";
    Teste_compress(p_mr, "mr", comp_dir);
    Teste_decompress(comp_dir, "mr", rest_dir);

    const char* p_nci = "silesia/nci";
    Teste_compress(p_nci, "nci", comp_dir);
    Teste_decompress(comp_dir, "nci", rest_dir);

    const char* p_ooffice = "silesia/ooffice";
    Teste_compress(p_ooffice, "ooffice", comp_dir);
    Teste_decompress(comp_dir, "ooffice", rest_dir);

    const char* p_osdb = "silesia/osdb";
    Teste_compress(p_osdb, "osdb", comp_dir);
    Teste_decompress(comp_dir, "osdb", rest_dir);

    const char* p_reymont = "silesia/reymont";
    Teste_compress(p_reymont, "reymont", comp_dir);
    Teste_decompress(comp_dir, "reymont", rest_dir);

    const char* p_samba = "silesia/samba";
    Teste_compress(p_samba, "samba", comp_dir);
    Teste_decompress(comp_dir, "samba", rest_dir);

    const char* p_sao = "silesia/sao";
    Teste_compress(p_sao, "sao", comp_dir);
    Teste_decompress(comp_dir, "sao", rest_dir);

    const char* p_webster = "silesia/webster";
    Teste_compress(p_webster, "webster", comp_dir);
    Teste_decompress(comp_dir, "webster", rest_dir);

    const char* p_xray = "silesia/x-ray";
    Teste_compress(p_xray, "x-ray", comp_dir);
    Teste_decompress(comp_dir, "x-ray", rest_dir);

    const char* p_xml = "silesia/xml";
    Teste_compress(p_xml, "xml", comp_dir);
    Teste_decompress(comp_dir, "xml", rest_dir);

    printf("\nAll 12 files processed manually.\n");
}

void Compress_Decompress_Especifico(const char* comp_dir, const char* rest_dir) {
    const char* p_dickens = "silesia/dickens";

    printf("--- Iniciando Processamento Especifico: [dickens] ---\n");

    // --- TEMPO DA COMPRESSÃO ---
    clock_t start_comp = clock();
    Teste_compress(p_dickens, "dickens", comp_dir);
    clock_t end_comp = clock();
    double time_comp = (double)(end_comp - start_comp) / CLOCKS_PER_SEC;

    // --- TEMPO DA DESCOMPRESSÃO ---
    clock_t start_decomp = clock();
    Teste_decompress(comp_dir, "dickens", rest_dir);
    clock_t end_decomp = clock();
    double time_decomp = (double)(end_decomp - start_decomp) / CLOCKS_PER_SEC;

    char *comp_file = malloc(sizeof(char) * 60);
    snprintf(comp_file, 60, "%s/dickens.lz78", comp_dir);

    int uncompressed_size = findSize(p_dickens);
    int compressed_size = findSize(comp_file);

    // --- RELATÓRIO FINAL ---
    printf("\n========================================\n");
    printf("RELATORIO DE TEMPO [dickens]:\n");
    printf("  Compressao:    %.3f segundos\n", time_comp);
    printf("  Descompressao: %.3f segundos\n", time_decomp);
    printf("  Tempo Total:   %.3f segundos\n", time_comp + time_decomp);
    printf("========================================\n\n");

    printf("\n========================================\n");
    printf("RELATORIO DE COMPRESSAO [dickens]:\n");
    printf("  Antes:                  %d bytes\n", uncompressed_size);
    printf("  Depois:                 %d bytes\n", compressed_size);
    printf("  Racio de Compressao:    %.2f bytes\n", compressionRatio(p_dickens, comp_file));
    printf("========================================\n\n");

    // free(p_dickens);
    free(comp_file);
}

void Teste_String_Manual(const char* comp_dir, const char* rest_dir) {
        char input_string[1024];
        const char* temp_name = "manual_test";

        printf("Digite a frase: ");

        // 1. Capturar a String
        if (fgets(input_string, sizeof(input_string), stdin) == NULL) return;
        input_string[strcspn(input_string, "\n")] = 0; // Limpar o \n

        // 2. Criar um ficheiro temporário com o que escreveu
        FILE* f_temp = fopen("temp_input.txt", "w+b");
        if (!f_temp) return;
        fwrite(input_string, 1, strlen(input_string), f_temp);
        rewind(f_temp); // Volta ao início para o compressor ler

        // 3. Comprimir
        printf("\n[PASSO 1] Comprimindo...\n");
        compress_and_save_logic_debug(f_temp, comp_dir, temp_name);
        fclose(f_temp);

         char path_to_compressed[256];
        snprintf(path_to_compressed, sizeof(path_to_compressed), "%s/%s.lz78", comp_dir, temp_name);

         FILE* f_comp = fopen(path_to_compressed, "rb");
    if (f_comp) {
        printf("\n[PASSO 2] Descomprimindo com Visualizacao...\n");
        // Usamos a mesma assinatura: (FILE* input, const char* folder, const char* name)
        decompress_and_save_debug(f_comp, rest_dir, temp_name);
        fclose(f_comp);
    }
        // 5. Mostrar o Resultado Final
        char restored_path[256];
        snprintf(restored_path, sizeof(restored_path), "%s/%s", rest_dir, temp_name);

        FILE* f_res = fopen(restored_path, "r");
        if (f_res) {
            char output_result[1024];
            fgets(output_result, sizeof(output_result), f_res);
            printf("\nRESULTADO FINAL RESTAURADO:\n\"%s\"\n", output_result);
            fclose(f_res);
        }
        printf("========================================\n\n");
    }