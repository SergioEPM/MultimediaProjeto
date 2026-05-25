# MultimediaProjeto

Projeto final da cadeira de Multimédia 2 do curso de Engenharia Informática da Universidade Fernando Pessoa dos alunos Sérgio Magalhães, [Diogo Oliveira](https://github.com/DiogoOliveira04ufp) e [João Nascimento](https://github.com/13JPNascimento).


## Acerca do projeto
Consiste numa implementação do algoritmo de compressão sem perdas LZ78 com um dicionário de hash table em C. Funciona a partir de testes pré-concebidos que serão chamados na função `main()` de acordo com o objetivo a demonstrar.

Ainda inclui cálculos da entropia dos ficheiros e do rácio de compressão.

## Testes incluídos

Para executar o programa terá de se escolher o teste que se quer executar e editar o `main()`. Estes são os testes.

* `Compress_Decompress_Especifico()` - Faz a compressão e descompressão de apenas um ficheiro que terá de ser passado pelos argumentos da função.
* `Compress_Decompress_ALL()` - Faz a compressão e descompressão de todos os ficheiros no silesia.
* `Teste_String_Manual()` - Faz a compressão e descompressão de uma string introduzida pelo utilizador.
* `testeEntropia()` - Executa a função do cálculo da entropia num ficheiro específico.

## Como compilar o código e executar

Este é um projeto CMake portanto será necessário instalar o CMake primeiro.

Poderá ser compilado e executado com estes comandos:

* Unix (Mac/Linux):
```sh
cmake -S . -B build     # Apenas necessário antes de compilar pela primeira vez
cmake --build build
./build/MultimediaProjeto
```

* Windows (PowerShell):
```ps1
cmake -S . -B build     # Apenas necessário antes de compilar pela primeira vez
cmake --build build
.\build\MultimediaProjeto.exe
```