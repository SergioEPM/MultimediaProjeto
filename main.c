#include <stdio.h>
#include <sys/stat.h>
#include "TestesCode.h"

/**
 * @mainpage LZ78 Compression Project
 *
 * ## Overview
 * This project implements the LZ78 algorithm for multimedia data compression.
 * It features a high-performance Hash Table implementation to ensure O(1)
 * average-time complexity during dictionary lookups.
 *
 * ## Key Modules
 * - **Compression:** Handles dictionary building and token generation.
 * - **Decompression:** Reconstructs original data using a stack-based walk.
 * - **Test Suite:** Includes automated testing for the Silesia Corpus.
 *
 * ## How to Navigate
 * Use the tabs above to explore the **Classes** (structs like HashEntry)
 * or **Files** to see the documented functions.
 */


/// Main function that allows to change the type of run
/// 1-All files
/// 2-Especific file
/// 3-Insert String
/// @return
int main(void) {
    // Variable names for your folders
    const char* comp_dir = "silesia_compress";
    const char* rest_dir = "silesia_restored";

    mkdir(comp_dir, 0777);
    mkdir(rest_dir, 0777);

    //Compress e decompress só especifico!
    //Compress_Decompress_Especifico(comp_dir, rest_dir);


    //Compresss e decompress todos os ficheiros!
    //Compress_Decompress_ALL(comp_dir, rest_dir);

    //Teste Manual
    Teste_String_Manual(comp_dir,rest_dir);

    return 0;
}