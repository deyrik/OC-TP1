#include "tp.h"

/*------------------------->   Montador RISC-V (versão simplificada)    <-------------------------*/

/*  O montador suportar um subconjunto de instruções formado à partir de: 
 *      lb   -> ok
 *      lh   -> ok
 *      lw   -> ok

 *      addi -> ok
 *      ori  -> ok
 *      andi -> ok

 *      sb   -> ok
 *      sh   -> ok
 *      sw   -> ok

 *      add  -> ok
 *      sub  -> ok
 *      sll  -> ok
 *      xor  -> ok
 *      srl  -> ok
 *      or   -> ok
 *      and  -> ok

 *      beq  -> ok
 *      bne  -> ok 
 *      jalr -> ok
 */

/*  Grupo 12
 *      Instruções principais:
 *          lw   -> ok
 *          sw   -> ok
 *          sub  -> ok
 *          xor  -> ok
 *          addi -> ok
 *          srl  -> ok
 *          beq  -> ok
 */

/*  Pseudos Instruções
 *      nop              addi x0, x0, 0   -> ok
 *      mv rd, rs        addi rd, rs, 0   -> ok
 *      neg rd, rs       sub  rd, x0, rs  -> ok
   
 *      jr rs            jalr x0, rs, 0   -> ok
 *      jalr rs          jalr x1, rs, 0   -> ok
 *      ret              jalr x0, x1, 0   -> ok         
 */

/*  cmd  opcode  f3    f7

 *  tipo    R
 *  ADD  0110011 000 0000000
 *  SUB  0110011 000 0100000
 *  SLL  0110011 001 0000000
 *  XOR  0110011 100 0000000
 *  SRL  0110011 101 0000000
 *  OR   0110011 110 0000000
 *  AND  0110011 111 0000000

 *  tipo    I
 *  LB   0000011 000
 *  LH   0000011 001
 *  LW   0000011 010

 *  ADDI 0010011 000
 *  ORI  0010011 110
 *  ANDI 0010011 111
 
 *  SB   0100011 000  
 *  SH   0100011 001
 *  SW   0100011 010

 *  BEQ  1100011 000
 *  BNE  1100011 001
 *  JALR 1100111 000
 */

/*  formato R
 *   funct7  rs2   rs1   f3  rd    opcode
 *   0000000 00000 00000 000 00000 0000000

 *   formato I
 *   immediate     rs1   f3  rd    opcode
 *   000000000000  00000 000 00000 0000000
 */

/*  Suporte a outras bases numéricas no arquivo .asm;
 *      Decimal     -> ok
 *      Hexadecimal
 *      Binário
 */

/*  Implementação de outras instruções fora do conjunto utilizado para gerar a combinação de cada grupo.
 *      lb   -> ok
 *      lh   -> ok

 *      ori  -> ok
 *      andi -> ok

 *      sb   -> ok
 *      sh   -> ok

 *      add  -> ok
 *      sll  -> ok
 *      or   -> ok
 *      and  -> ok

 *      bne  -> ok 
 *      jalr -> ok
 */


/*  A função intToBin recebe um número inteiro num e um inteiro n, que representa o tamanho da string binária 
 * de saída. A função converte o valor de num em uma string binária de tamanho n e retorna essa string.
 */
char* intToBin(int num, int n){
    
    int x, y, z;

    x = num;

    char* resultado = (char*) malloc (n+1);

    if (resultado == NULL){
        printf("Erro: Falha na alocacao de memoria para o resultado (arquivo: tp.c; linha: 97)\n");
    }
    
    for(z = n-1; z >= 0; z--){
        y = x >> z;

        if (z == n-1){
            if(y & 1) {
                strcpy(resultado, "1");
            } 
            else {
                strcpy(resultado, "0");
            }
        } 
        else {
            if(y & 1) {
                strcat(resultado, "1");
            } 
            else {
                strcat(resultado, "0");
            }
        }
    }

    return resultado;
}

/*  A função recebe cinco ponteiros para strings (f7, f3, p1, p2, p3) e um ponteiro para um ponteiro 
*   para string (bin).
*   A função é responsável por montar o código de operação da instrução do tipo R para a arquitetura 
*   RISC-V e armazená-lo na string apontada por bin.
*/
void tipoR(char* f7, char* f3, char* p1, char* p2, char* p3, char** bin){
    // Resultado parcial do binário
    //char resultado[33];
        // Inicializa a string com zeros
    char resultado[33] = {0};

    // Concatena as strings
    strcat(resultado, f7);
    strcat(resultado, p3);
    strcat(resultado, p2); 
    strcat(resultado, f3);
    strcat(resultado, p1);
    strcat(resultado, "0110011"); 

    // Copia resultado para bin
    strcpy(*bin, resultado);
}


/*  A função recebe cada um dos parâmetros que compõem uma string completa 
*   de um comando RISC-V convertido para linguagem de máquina e o concatena na 
*   ordem necessária.
*/
void tipoI(char* f3, char* p1, char* p2, char* p3, char ** bin, char* comando) {
    // Resultado parcial do binário
   //char resultado[33];
        // Inicializa a string com zeros
    char resultado[33] = {0};

    char* cmd = comando;

    // Concatena as strings
    strcat(resultado, p3); // imediato
    strcat(resultado, p2); // rs1
    strcat(resultado, f3); // funct 3
    strcat(resultado, p1); // rd

    if (!strcmp(cmd, "lw")){
       strcat(resultado, "0000011");
    }
    else if (!strcmp(cmd, "sw")){
        strcat(resultado,"0100011");
    }
    else if (!strcmp(cmd, "beq")){
        strcat(resultado,"1100011");
    }
    else if (!strcmp(cmd, "jalr")){
        strcat(resultado,"1100111");
    }
    else if (!strcmp(cmd, "lh")){
        strcat(resultado,"0000011");
    }
    else if (!strcmp(cmd, "bne")){
        strcat(resultado,"1100011");
    }
    else if (!strcmp(cmd, "addi")){
        strcat(resultado,"0010011");
    }
    else if (!strcmp(cmd, "nop")){
        strcat(resultado,"0010011");
    }
    else if (!strcmp(cmd, "mv")){
        strcat(resultado,"0010011");
    }
    else if (!strcmp(cmd, "lb")){
        strcat(resultado,"0000011");
    }
    else if (!strcmp(cmd, "ori")){
        strcat(resultado,"0010011");
    }

    else{
        strcat(resultado, "0100011"); // cmd //sb , sw, sh 
    }

    // Copia resultado para bin
    strcpy(*bin, resultado);

}


/*  Principal função do código
*   Essa função recebe como entrada um comando de montagem (por exemplo, "add" ou "sub") e até três 
*   parâmetros. Em seguida, ela converte os parâmetros de string para inteiros usando a função strtol e 
*   chama uma das funções tipoR ou tipoI dependendo do comando.
*/
void montadorBinario(char* comando, char* p1, char* p2, char* p3, char** bin) {
    int p1n;
    int p2n;
    int p3n;

    // Converte uma string em um valor int
    p1n = (int) strtol(p1, (char **)NULL, 10);
    p2n = (int) strtol(p2, (char **)NULL, 10);
    p3n = (int) strtol(p3, (char **)NULL, 10);

    // strcmp compara duas strings, se iguais entra-se no bloco do if
    if (!strcmp(comando, "add")){
        tipoR("0000000", "000", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 5), bin); 
        return;
    }
    if (!strcmp(comando, "sub")){
        tipoR("0100000", "000", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 5), bin); 
        return;
    }
    if (!strcmp(comando, "and")){
        tipoR("0000000", "111", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 5), bin); 
        return;
    }
    if (!strcmp(comando, "or")){
        tipoR("0000000", "110", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 5), bin); 
        return;
    }
    if (!strcmp(comando, "xor")){
        tipoR("0000000", "100", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 5), bin); 
        return;
    }
    if (!strcmp(comando, "sll")){
        tipoR("0000000", "001", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 5), bin); 
        return;
    }
    if (!strcmp(comando, "srl")){
        tipoR("0000000", "101", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 5), bin); 
        return;
    }
    if (!strcmp(comando, "addi")){
        tipoI("000", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 12), bin, comando); 
        return;
    }
    if (!strcmp(comando, "andi")){
        tipoI("111", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 12), bin, comando); 
        return;
    }
    if (!strcmp(comando, "ori")){
        tipoI("110", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 12), bin, comando); 
        return;
    }
    if (!strcmp(comando, "lw")){
        tipoI("010", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 12), bin, comando); 
        return;
    }
    if (!strcmp(comando, "sw")){
        tipoI("010", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 12), bin, comando); 
        return;
    }
    if (!strcmp(comando, "beq")){
        tipoI("000", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 12), bin, comando); 
        return;
    }
    if (!strcmp(comando, "jalr")){
        tipoI("000", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 12), bin, comando); 
        return;
    }
    if (!strcmp(comando, "lb")){
        tipoI("000", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 12), bin, comando); 
        return;
    }
    if (!strcmp(comando,"lh")){
        tipoI("001", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 12), bin, comando); 
        return;
    }
    if (!strcmp(comando,"sb")){
        tipoI("000", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 12), bin, comando); 
        return;
    }
    if (!strcmp(comando,"sh")){
        tipoI("001", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 12), bin, comando); 
        return;
    }
    if (!strcmp(comando,"bne")){
        tipoI("001", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(p3n, 12), bin, comando); 
        return;
    }

    //pseudo instruções: 

    if (!strcmp(comando,"nop")){
        tipoI("000", intToBin(0, 5), intToBin(0, 5), intToBin(0, 12), bin, comando); 
        return;
    }  
    if (!strcmp(comando,"mv")){
        tipoI("000", intToBin(p1n, 5), intToBin(p2n, 5), intToBin(0, 12), bin, comando); 
        return;
    }
    if (!strcmp(comando, "neg")){
        tipoR("0100000", "000", intToBin(p1n, 5), intToBin(p3n, 5), intToBin(p2n, 5), bin);
        return;
    }
    if (!strcmp(comando, "jr")){
        tipoI("000", intToBin(p2n, 5), intToBin(p1n, 5), intToBin(p3n, 12), bin, comando);
        return;
    }
    if (!strcmp(comando, "ret")){
        tipoI("000", intToBin(0, 5), intToBin(1, 5), intToBin(0, 12), bin, comando); 
        return;
    }
    if (!strcmp(comando, "pjr")){
        tipoI("000", intToBin(1, 5), intToBin(p2n, 5), intToBin(0, 12), bin, comando); 
        return;
    }
    
}

/*  Esta função formata uma string que representa um registrador
*
*   A função vai receber cada linha do arquivo de entrada (str) e vai retirar os “x” e as virgulas no 
*   final de cada registrador
*/
char* formatRegs(char *str){

    // strlen retorna tanho da string
    if (str[strlen(str)-1] == ',' || str[strlen(str)-1] == ')'){
        str[strlen(str)-1] = '\0';
    }
    if (str[0] == 'x'){

        //usada para copiar blocos de memória de um endereço de origem para um endereço de destino.
        memmove(str, str+1, strlen(str));
    }

    return str;
}


/*  Essa função recebe uma string contendo uma instrução assembly e converte essa instrução em sua 
*   representação binária correspondente. 
*
*   A função montarBinário vai pegar cada segmento de uma linha do arquivo de entrada (str) e salvará 
*   em uma variável correspondente.
*/
void montarBinario(char * str, char **bin) {
    char *instrucao;
    char *comando;
    char *copComando;
    char *p1 = "0";
    char *p2 = "0";
    char *p3 = "0";
    int i = 0;

    /*  Usada para separa uma string em uma série de tokens (palavras) separadas por um delimitador 
    *   específico.
    */
    instrucao = strtok(str, " ");

    while (instrucao != NULL){

        if (i == 0) 
        {
            comando = instrucao;
        }


        if (i == 1) 
        {
            p1 = formatRegs(instrucao);
        }


        if (i == 2) 
        {
            if(!strcmp(comando, "lw") || !strcmp(comando, "sw") || !strcmp(comando, "lb") || !strcmp(comando, "lh") || !strcmp(comando, "sb") || !strcmp(comando, "sh")) 
            {
                char auxImediato = instrucao[0];
                p3 = formatRegs(&auxImediato);
                memmove(instrucao, instrucao+2, strlen(instrucao));
                p2 = formatRegs(instrucao);       
            }

            else
            {
                p2 = formatRegs(instrucao);
            }
        }

            /* 
           if(!strcmp(comando, "jalr"))
           {

            
                if (i == 0)
                {
                    strcpy(copComando, comando);
                    strcpy(comando, "pjr");//pseudo jalr 
                }
                if (i > 1)
                {
                    strcpy(comando, copComando);
                } 
            } 
            */

        if(strcmp(comando, "lw") && strcmp(comando, "sw") && strcmp(comando, "lb")  && strcmp(comando, "lh") && strcmp(comando, "sb") && strcmp(comando, "sh")) {
            if (i == 3) {
                p3 = formatRegs(instrucao);        
            }
        }
        

        i += 1;

        //A função deve continuar a extrair tokens da mesma string que foi usada na primeira chamada.
        instrucao = strtok (NULL, " ");
    }

    montadorBinario(comando, p1, p2, p3, bin);
}