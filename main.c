#include <stdio.h>
#include <sys/stat.h>
#include "TestesCode.h"


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