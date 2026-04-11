#include "compress.h"
#include <stdlib.h>
#include <string.h>

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