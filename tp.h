#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char * intToBin(int num, int n);

void tipoR(char* f7, char* f3, char* p1, char* p2, char* p3, char ** bin);

void tipoI(char* f3, char* p1, char* p2, char* p3, char ** bin, char* comando);

void montadorBinario(char* comando, char* p1, char* p2, char* p3, char** bin);

char* formatRegs(char *str);

void montarBinario(char * str, char **bin);