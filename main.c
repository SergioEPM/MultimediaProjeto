#include <stdio.h>
#include <sys/stat.h>
#include "compress.h"

FILE* OpenFile(char* filename) {
   FILE* fptr = fopen(filename, "r");
   if (fptr == NULL) {
      fprintf(stderr, "Error: Could not open file %s\n", filename);
   }
   return fptr;
}

void Teste_only_1(const char* folder) {
   const char* in_path = "silesia/dickens";



   // 2. Open file with your function
   FILE* ficheiro_a_comprimir = OpenFile((char*)in_path);

   if (ficheiro_a_comprimir != NULL) {
     //3.Excecute the Compressing
      compress_and_save_logic(ficheiro_a_comprimir, folder, "dickens");

      fclose(ficheiro_a_comprimir);
   }
}




int main(void) {
   const char* out_folder = "silesia_compress";
   // 1. Create the folder in main
   mkdir(out_folder, 0777);

   Teste_only_1(out_folder);
   return 0;
}