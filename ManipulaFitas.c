#include<stdio.h>
#include<stdlib.h>
#include"ManipulaFitas.h"

void criaFitas(void){//CRIA AS FITAS A SEREM USADAS
    FILE *arq;
    char nome[15];

    comp++;
    int i;
    for(i=1; i<=MaxF; i++){
        sprintf(nome, "fita%d.bin", i);
        comp+=2;
        if((arq = fopen(nome, "wb")) == NULL){
            printf("Erro na criacao da fita%d.bin!", i);
            return;
        }
        fclose(arq);
    }
}

void converteProvao(RegHeap registro){//CONVERTE DE ARQUIVO BINARIO PARA TXT
    FILE *arq;
    FILE *fita;
    char nome[15];

    arq = fopen("PROVAO_ORDENADO.txt", "w");
    sprintf(nome, "fita%d.bin", registro.origem);
    fita = fopen(nome, "rb");

    while(fread(&registro, sizeof(RegHeap), 1, fita) == 1){
        comp++;
        fprintf(arq,"%-9ld%-6.2lf%-3s%-51s%-30s\n" ,registro.matricula, registro.nota, registro.estado, registro.cidade, registro.curso);
    }
    fclose(fita);
    fclose(arq);
}

void imprimeProvao(void){ //IMPRIME O ARQUIVO TXT
    Reg aux;
    FILE *arq;
    char enter;

    int i=1;

    arq = fopen("PROVAO_ORDENADO.txt", "r");
    while(fscanf(arq, "%ld %lf %[A-Z a-z ' -] %[\n]", &aux.matricula, &aux.nota, aux.cidade, enter) != EOF){
        printf("%-9ld%-6.2lf%-51s\n", aux.matricula, aux.nota,aux.cidade);
        //printf("%d\n", i);
        i++;
    }
}
