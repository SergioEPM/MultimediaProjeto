#include "funcoes.h"

FILE* OpenFile(char* filename) {
    FILE* fptr = fopen(filename, "rb");
    if (fptr == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
    }
    return fptr;
}

long int findSize(const char file_name[])
{
    // opening the file in read mode
    FILE* fp = fopen(file_name, "r");

    // checking if the file exist or not
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);

    // calculating the size of the file
    long int res = ftell(fp);

    // closing the file
    fclose(fp);

    return res;
}

float compressionRatio(const char *uncompressed_path, const char *compressed_path)
{
    int uncomp_size = findSize(uncompressed_path);
    int comp_size = findSize(compressed_path);

    float result = 0.0;

    result = (float)uncomp_size / (float)comp_size;

    return result;
}

float compressionEntropy(const char *file_path)
{
    int freq[256] = {0};
    int c = 0;              // caracter atual, convertido de char para int
    int value_count = 0;    // contagem dos valores totais do ficheiro para a conta das probabilidades

    float entropy = 0.0;

    FILE *fptr = fopen(file_path, "r");
    if(fptr == NULL)
    {
        fprintf(stderr, "Error: Could not open file %s\n", file_path);
        return -1;
    }

    while((c = fgetc(fptr)) != EOF)
    {
        freq[(unsigned char)c]++;       // conta a frequência do caracter específico
        value_count++;                  // incrementa a conta dos caracteres totais
    }

    // ciclo for() para o somatório
    for(int i = 0; i < 256; i++)
    {
        if(freq[i] > 0)
        {
            float probability = (float)freq[i] / (float)value_count;
            entropy = entropy + (probability * log(probability));
        }
    }

    entropy = -entropy;     // sinal tem de trocar no fim

    fclose(fptr);
    return entropy;
}