//
// Created by clonic on 4/15/26.
//

#ifndef MULTIMEDIAPROJETO_TESTESCODE_H
#define MULTIMEDIAPROJETO_TESTESCODE_H
#include <stdio.h>

/**
 * @file TestesCode.h
 * @brief Header file containing testes and calling the right functions.
 */


/**
 * @brief Helper function to safely open files.
 * Provides a centralized way to open files in binary read mode with
 * built-in error reporting to stderr.
 * * @param filename The path/name of the file to open.
 * @return FILE* A pointer to the opened file, or NULL if it failed.
 */
FILE* OpenFile(char* filename);

/**
 * @brief Unit test wrapper for the compression stage.
 * Opens a specific source file, runs the compression logic, and ensures
 * the file handle is closed properly afterward.
 * * @param in_path Full path to the original file.
 * @param name The name to be used for the compressed output.
 * @param folder The destination directory for the .lz78 file.
 */
void Teste_compress(const char* in_path, const char* name, const char* folder);

/**
 * @brief Unit test wrapper for the decompression stage.
 * Locates the .lz78 file in the input folder and restores it to the
 * output folder.
 * * @param in_folder Where the compressed file is currently stored.
 * @param name The base name of the file (without extension).
 * @param out_folder The destination for the restored .txt file.
 */
void Teste_decompress(const char* in_folder, const char* name, const char* out_folder);

/**
 * @brief Batch processor for the Silesia Corpus.
 * Manually iterates through all 12 standard files in the Silesia dataset
 * (dickens, mozilla, etc.), performing a full compression/decompression
 * cycle on each.
 * * @param comp_dir Directory to store compressed files.
 * @param rest_dir Directory to store restored files.
 */
void Compress_Decompress_ALL(const char* comp_dir, const char* rest_dir);

/**
 * @brief Performance benchmarking tool for a specific file.
 * Compresses and decompresses the "dickens" file while tracking execution
 * time using the clock() function. Prints a detailed report of the
 * time taken for each stage.
 * * @param comp_dir Directory for the compressed output.
 * @param rest_dir Directory for the restored output.
 */
void Compress_Decompress_Especifico(const char* comp_dir, const char* rest_dir);

/**
 * @brief Interactive debug mode for custom string testing.
 * Allows the user to type a phrase in the console, saves it to a temporary
 * file, and runs the "Visual Debug" versions of both compression and
 * decompression to show exactly how the LZ78 dictionary evolves.
 * * @param comp_dir Directory for temporary compressed data.
 * @param rest_dir Directory for temporary restored data.
 */
void Teste_String_Manual(const char* comp_dir, const char* rest_dir);

#endif //MULTIMEDIAPROJETO_TESTESCODE_H
