#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Heap.h"

void converteReg(Reg registro, RegHeap *novoReg){
    novoReg->matricula = registro.matricula;
    novoReg->nota = registro.nota;
    strcpy(novoReg->cidade, registro.cidade);
    strcpy(novoReg->curso, registro.curso);
    strcpy(novoReg->estado, registro.estado);

    novoReg->origem = 0;
    novoReg->ultimo = 0;
    novoReg->pos = 0;
}

void heapRefaz(RegHeap *vetor, int esq, int dir){
    int i=esq;
    int j=i*2+1;// PRIMEIRO FILHO DE I
    RegHeap aux = vetor[i];

    while(j<=dir){
        comp+=3;
        if(j<dir && vetor[j].nota < vetor[j+1].nota)
            j++; //RECEBE O OUTRO FILHO DE I
        if(aux.nota >= vetor[j].nota)
            break;
        vetor[i] = vetor[j];
        i=j;
        j=i*2+1;
    }
    vetor[i] = aux;
}

void heapConstroi(RegHeap *vetor, int n){
    int esq;
    esq = (n/2)-1;
    while(esq >= 0){
        comp++;
        heapRefaz(vetor, esq, n-1);
        esq--;
    }
}
