#ifndef QuickSort_h
#define QuickSort_h

#include<stdio.h>
#include<stdlib.h>
#include"Reg.h"
#include"Arq.h"

#define TAM_AREA 15
#define INT_MAX -1.0
#define INT_MIN 101.0

typedef struct TipoArea{
    Reg regs[TAM_AREA];
    int celOcup;
}TipoArea;

void quicSort(unsigned long);
void quickSortExt(FILE**, FILE**, FILE**, long, long);
void particao(FILE**, FILE**, FILE**, TipoArea, long, long, long*, long*);
void leSup(FILE**, Reg*, long*, short*);
void leInf(FILE**, Reg*, long*, short*);
void inserirArea(TipoArea*, Reg*, int*);
void escreveMax(FILE**, Reg, long*);
void escreveMin(FILE**, Reg, long*);
void retiraMax(TipoArea*, Reg*, int*);
void retiraMin(TipoArea*, Reg*, int*);


void FAVazia(TipoArea*);
void insereItem(Reg, TipoArea*);
int  obterNumCelOcp(TipoArea*);
void retiraUltimo(TipoArea*, Reg*);
void retiraPrimeiro(TipoArea*, Reg*);

#endif
