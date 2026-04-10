#include "compress.h"
#include <stdlib.h>

// This is where your dictionary logic will live
void lz78_compress_logic(FILE* input, FILE* output) {
    int c;
    int dictionary_index = 0;

    printf("Running LZ78 Logic...\n");

    // LZ78 reads one character at a time until the end of the file (EOF)
    while ((c = fgetc(input)) != EOF) {

        ///TODO: MAKE LOGIC for LZ78
        ///
        fputc(c, output);
    }
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