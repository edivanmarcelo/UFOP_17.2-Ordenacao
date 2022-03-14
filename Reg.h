#ifndef REG_H_INCLUDED
#define REG_H_INCLUDED
#include <string.h>
#include <time.h>

clock_t tempo; //Tempo do programa
unsigned long comp;      //Num. de comparacoes
unsigned long leituras;     //Num. de leituras do arquivo
unsigned long escritas;     //Num. de escritas do arquivo

typedef struct reg
{
    long int matricula;
    double nota;
    char estado[3];
    char cidade[50];
    char curso[30];
}Reg;

#endif // REG_H_INCLUDED
