#include <stdio.h>
#include <sys/stat.h>
#include "compress.h"
#include "decompress.h"

FILE* OpenFile(char* filename) {
   // Updated to "rb" because LZ78 outputs binary data
   FILE* fptr = fopen(filename, "rb");
   if (fptr == NULL) {
      fprintf(stderr, "Error: Could not open file %s\n", filename);
   }
   return fptr;
}

void Teste_only_1_compress(const char* folder) {
   const char* in_path = "silesia/dickens";
   FILE* ficheiro_a_comprimir = OpenFile((char*)in_path);

   if (ficheiro_a_comprimir != NULL) {
      compress_and_save_logic(ficheiro_a_comprimir, folder, "dickens");
      fclose(ficheiro_a_comprimir);
   }
}

void Teste_only_1_decompress(const char* in_folder, const char* out_folder) {
   // We look for the file inside the compression output folder
   char compressed_path[256];
   snprintf(compressed_path, sizeof(compressed_path), "%s/dickens.lz78", in_folder);

   FILE* ficheiro_a_descomprimir = OpenFile(compressed_path);

   if (ficheiro_a_descomprimir != NULL) {
      // Execute the Decompressing
      decompress_and_save(ficheiro_a_descomprimir, out_folder, "dickens");
      fclose(ficheiro_a_descomprimir);
   }
}

int main(void) {
   const char* comp_folder = "silesia_compress";
   const char* rest_folder = "silesia_restored";

   // 1. Create folders
   mkdir(comp_folder, 0777);
   mkdir(rest_folder, 0777);

   // 2. Run Compression test
   Teste_only_1_compress(comp_folder);

   // 3. Run Decompression test
   Teste_only_1_decompress(comp_folder, rest_folder);

   return 0;
}