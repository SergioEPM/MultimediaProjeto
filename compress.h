#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @def MAX_DICT_SIZE
 * @brief The maximum number of entries allowed in the LZ78 dictionary.
 * Limited to 65535 to fit within an unsigned short (2 bytes).
 */

/**
 * @def HASH_SIZE
 * @brief The size of the Hash Table array.
 * Uses a prime number (131071) significantly larger than the dictionary size
 * to minimize hash collisions and maintain O(1) average lookup time.
 */
#define MAX_DICT_SIZE 65535
#define HASH_SIZE 131071 // Prime number > MAX_DICT_SIZE


/**
 * @struct HashEntry
 * @brief Represents a single node in the compression dictionary.
 * * This structure maps a sequence (prefix + character) to a specific dictionary index.
 * Total size: 5 bytes (plus potential compiler padding).
 * * @var HashEntry::prefix_index
 * The dictionary index of the existing sequence before the current character.
 * * @var HashEntry::character
 * The new character being appended to the prefix to form a new sequence.
 * * @var HashEntry::dict_idx
 * The unique identifier assigned to this new sequence for future reference.
 */
typedef struct {
    unsigned short prefix_index; // 2 bytes
    char character;              // 1 byte
    unsigned short dict_idx;     // 2 bytes
} HashEntry;

/**
 * @brief Simple hash function for the dictionary lookup.
 * Combines the current prefix index and the next character to generate a hash key.
 * * @param prefix The index of the already existing sequence in the dictionary.
 * @param c The next character in the input stream.
 * @return unsigned int The calculated hash index within HASH_SIZE.
 */
unsigned int hash_func(unsigned short prefix, char c) ;



/**
 * @brief Core LZ78 compression algorithm using a Hash Table.
 * Reads characters one by one, searches for the longest existing prefix in the
 * dictionary, and writes (prefix_index, next_char) pairs to the output file.
 * * @param input Pointer to the opened source file (text/binary).
 * @param output Pointer to the opened .lz78 destination file.
 */
void lz78_compress_logic(FILE* input, FILE* output);


/**
 * @brief Handles file I/O boilerplate for standard compression.
 * Generates the target file path, opens the binary output stream, and triggers
 * the compression logic.
 * * @param input Pointer to the source file.
 * @param folder The destination directory string.
 * @param filename The original name of the file (to be appended with .lz78).
 */
void compress_and_save_logic(FILE* input, const char* folder, const char* filename);



/**
 * @brief Debug helper to visualize the state of the Hash Table.
 * Iterates through the hash table and prints the first 50 entries, showing
 * how sequences are mapped to dictionary indices.
 * * @param hash_table Pointer to the calloc'd HashEntry array.
 */
void print_final_dictionary(HashEntry* hash_table);


/**
 * @brief An instrumented version of the LZ78 algorithm for educational purposes.
 * Performs compression while printing a step-by-step trace of dictionary hits
 * (EXISTE) and misses (NOVO) to the console.
 * * @param input Pointer to the source file.
 * @param output Pointer to the binary output file.
 */
void lz78_visual_debug(FILE* input, FILE* output);



/**
 * @brief Wrapper for the visual debug mode.
 * Same as the standard logic, but redirects the compression task to
 * lz78_visual_debug for real-time console tracking.
 * * @param input Pointer to the source file.
 * @param folder The destination directory string.
 * @param filename The original name of the file.
 */
void compress_and_save_logic_debug(FILE* input, const char* folder, const char* filename);


#endif
