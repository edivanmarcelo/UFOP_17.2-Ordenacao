#ifndef Heap_h
#define Heap_h

#include"Reg.h"

typedef struct RegHeap{
    long int matricula;
    double nota;
    char estado[3];
    char cidade[50];
    char curso[30];

    int origem;
    int pos;
    short ultimo;
}RegHeap;

void converteReg(Reg, RegHeap*);
void heapRefaz(RegHeap*, int, int);
void heapConstroi(RegHeap*, int);

#endif
