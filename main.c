#include "tp.h"
#include <string.h>


/*Formas de Exibir o resultado:
*   Terminal:
*       Caso o cliente passe por linha de comando somente o arquivo .asm
*   Arquivo:
*       Caso o cliente passe por linha de comando uma entrada convencional de compiladores
*/

/*  argc e argv
*
*   argv e um vetor de strings
*       Recebe os parâmetros passado na linha de comando
*
*   argc e o numero de parâmetros
*/

int main(int argc, char const *argv[]){

    printf("\033[H\033[J");

    /*------------------------->   Manipulação de arquivo   <-------------------------*/
    FILE *pontInp;
    FILE *pontOut;

    // Armazena a linha do arquivo de entrada
    char str[50];

    /* Aloca um espaço de memoria de 33 bits para salvar o binário
       Poderia tambem usar um vetor de char
    */  
    char* bin = (char *) malloc(33);
    //  Armazena o nome do arquivo de entrada
    char entrada[50];
    char saida[50] = "saida_";
    char strTest[50] = "test/";
    char strBin[50] = "bin/";
    
    /*------------------------->    Saida por Arquivo   <-------------------------*/
    if (argc >= 1 ){


        // Copia a posição 1 do argv para a entrada, que e o nome do arquivo de entrada
        strcpy(entrada, argv[1]);
        strcpy(saida, argv[3]);

        //  Abertura do arquivo de entrada e criação do de saída

        pontInp = fopen(entrada, "r"); 
        pontOut = fopen(saida, "w");
 
    
        //  Verificando se abertura dos arquivos deram certo
        if (pontInp == NULL){
            printf("Erro: Arquivo de entrada não pode ser aberto!  (arquivo: main.c; linha: 38)\n");
        }
        if (pontOut == NULL){
            printf("Erro: Arquivo de saiada não pode ser criado!  (arquivo: main.c; linha: 39)\n");
        }

        /* fgets vai pega cada linha do arquivo de entrada
        *       Retorna NULL se ocorrer um erro ou se chegar ao final do arquivo.
        */
        while (fgets(str, 50, pontInp) != NULL){

            // ...
            montarBinario(str, &bin);
            // Salva o bin no arquivo de saída
            fprintf(pontOut, "%s\n", bin);
        }
    }

    /*------------------------->    Saida por Terminal  <-------------------------*/
    else {

        printf("Insira o nome do arquivo de entrada: \n");
        scanf("%s", entrada);

        //  Abertura do arquivo de entrada e criação do de saída
        //pontInp = fopen(entrada, "a+");
        //("entradas/%s",entrada)
        pontInp = fopen(("entradas/%s",entrada), "r"); 
        pontOut = fopen((strcat(saida , entrada)), "w");
 

        //  Verificando se abertura dos arquivos deram certo
        if (pontInp == NULL){
            printf("Erro: Arquivo de entrada não pode ser aberto!  (arquivo: main.c; linha: 38)\n");
        }
        if (pontOut == NULL){
            printf("Erro: Arquivo de saiada não pode ser criado!  (arquivo: main.c; linha: 39)\n");
        }

        /* fgets vai pega cada linha do arquivo de entrada
        *       Retorna NULL se ocorrer um erro ou se chegar ao final do arquivo.
        */


       printf("\033[H\033[J");
       
        while (fgets(str, 50, pontInp) != NULL){

            // ...
            montarBinario(str, &bin);
            // Printa o bin no terminal
            printf("%s\n", bin);
        }
    }
    
    //  Fechamento do arquivo de entrada e saída
    fclose(pontInp);
    fclose(pontOut); 

    return 0;
}