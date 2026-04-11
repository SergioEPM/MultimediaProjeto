#include <stdio.h>
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

    // --- RELATÓRIO FINAL ---
    printf("\n========================================\n");
    printf("RELATORIO DE TEMPO [dickens]:\n");
    printf("  Compressao:    %.3f segundos\n", time_comp);
    printf("  Descompressao: %.3f segundos\n", time_decomp);
    printf("  Tempo Total:   %.3f segundos\n", time_comp + time_decomp);
    printf("========================================\n\n");
}
int main(void) {
    // Variable names for your folders
    const char* comp_dir = "silesia_compress";
    const char* rest_dir = "silesia_restored";

    mkdir(comp_dir, 0777);
    mkdir(rest_dir, 0777);

    //Compress e decompress só especifico!
    Compress_Decompress_Especifico(comp_dir, rest_dir);


    //Compresss e decompress todos os ficheiros!
    //Compress_Decompress_ALL(comp_dir, rest_dir);

    return 0;
}