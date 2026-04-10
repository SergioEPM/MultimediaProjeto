#include <stdio.h>


FILE* OpenFile(char* filename) {
   FILE* fptr;

   fptr = fopen(filename, "r");

   if (fptr == NULL) {

      fprintf(stderr, "Error: Could not open file %s\n", filename);
   }
   return fptr;
}

int main(void) {
   // Store the result in a pointer
   FILE* ficheiro_a_comrpimir = OpenFile("/home/clonic/CLionProjects/MultimediaProjeto/silesia/dickens");

   char data[50];

   if (ficheiro_a_comrpimir == NULL) {
      printf("File failed to open.\n");
      return 1; // Exit if file is missing
   } else {
      printf("The file is now opened.\n");

      // Use the pointer directly (no & needed)
      while (fgets(data, 50, ficheiro_a_comrpimir) != NULL) {
         printf("%s", data);
      }

      // Close using the pointer
      fclose(ficheiro_a_comrpimir);
   }

   return 0;
}