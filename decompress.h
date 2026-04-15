//
// Created by clonic on 4/10/26.
//

#ifndef MULTIMEDIAPROJETO_DECOMPRESS_H
#define MULTIMEDIAPROJETO_DECOMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compress.h"

/**
 * @file decompress.h
 * @brief Header file containing LZ78 decompression structures and prototypes.
 */



/**
 * @brief Core LZ78 decompression algorithm using an array-based dictionary.
 * Reconstructs the original data by reading (index, character) pairs. It uses a
 * stack-based approach to "walk back" through the dictionary and print sequences
 * in the correct order.
 * * @param input Pointer to the .lz78 compressed binary file.
 * @param output Pointer to the destination file for the restored data.
 */
void lz78_decompress_logic(FILE* input, FILE* output);

/**
 * @brief Handles file I/O boilerplate for standard decompression.
 * Generates the restored file path (e.g., adding "_restored.txt"), opens the
 * output stream, and executes the decompression logic.
 * * @param input Pointer to the compressed source file.
 * @param folder The destination directory string (e.g., "silesia_restored").
 * @param filename The base name of the file being restored.
 */
void decompress_and_save(FILE* input, const char* folder, const char* filename);


/**
 * @brief Instrumented decompression logic for real-time trace analysis.
 * Prints a step-by-step table to the console showing which token index is
 * being read, the new character added, and the full string sequence being
 * reconstructed from the dictionary.
 * * @param input Pointer to the compressed binary file.
 * @param output Pointer to the restored destination file.
 */
void lz78_decompress_visual_debug(FILE* input, FILE* output);


/**
 * @brief Wrapper for the visual decompression debug mode.
 * Prepares the output file and redirects the process to the visual
 * tracer (lz78_decompress_visual_debug) to monitor the dictionary reconstruction.
 * * @param input Pointer to the compressed source file.
 * @param folder The destination directory string.
 * @param filename The base name of the file.
 */
void decompress_and_save_debug(FILE* input, const char* folder, const char* filename);

#endif //MULTIMEDIAPROJETO_DECOMPRESS_H
