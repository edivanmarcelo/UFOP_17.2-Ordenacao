#include"QuickSort.h"

void quickSortExt(FILE **arqLi, FILE **arqEi, FILE **arqLEs, long esq, long dir){
    long i,j;
    TipoArea area; //AREA DE ARMAZENAMENTO INTERNO

    comp++;
    if(dir - esq < 1)
        return;

    FAVazia(&area);
    particao(arqLi, arqEi, arqLEs, area, esq, dir, &i, &j);

    comp++;
    if(i-esq<dir-j){ //ORDENA PRIMEIRO O SUBARQUIVO MENOR
        quickSortExt(arqLi, arqEi, arqLEs, esq, i);
        quickSortExt(arqLi, arqEi, arqLEs, j, dir);
    }
    else{
        quickSortExt(arqLi, arqEi, arqLEs, j, dir);
        quickSortExt(arqLi, arqEi, arqLEs, esq, i);
    }
}

void leSup(FILE **arqLEs, Reg *ultLido, long *Ls, short *ondeLer){
    fseek(*arqLEs, (*Ls-1)*sizeof(Reg), SEEK_SET);
    fread(ultLido, sizeof(Reg), 1, *arqLEs);
    (*Ls)--; *ondeLer = 0; leituras++;
}

void leInf(FILE **arqLi, Reg *ultLido, long *Li, short *ondeLer){
    fread(ultLido, sizeof(Reg), 1, *arqLi);
    (*Li)++; *ondeLer = 1; leituras++;
}

void inserirArea(TipoArea *area, Reg *ultLido, int *nArea){ //INSERE ULTlIDO DE FORA ORDENADA NA AREA
    insereItem(*ultLido, area);
    *nArea = obterNumCelOcp(area);
}

void escreveMax(FILE **arqLEs, Reg registro, long *Es){
    fseek(*arqLEs, (*Es-1)*sizeof(Reg), SEEK_SET);
    fwrite(&registro, sizeof(Reg), 1, *arqLEs);
    (*Es)--; escritas++;
}

void escreveMin(FILE **arqEi, Reg registro, long *Ei){
    fwrite(&registro, sizeof(Reg), 1, *arqEi);
    (*Ei)++; escritas++;
}

void retiraMax(TipoArea *area, Reg *registro, int *nArea){
    retiraUltimo(area, registro);
    *nArea = obterNumCelOcp(area);
}
void retiraMin(TipoArea *area, Reg *registro, int *nArea){
    retiraPrimeiro(area, registro);
    *nArea = obterNumCelOcp(area);
}

void particao(FILE **arqLi, FILE **arqEi, FILE **arqLEs, TipoArea area, long esq, long dir, long *i, long *j){
    long Ls=dir, Es=dir, Li=esq, Ei=esq;
    int nArea=0;
    double lInf=INT_MIN, lSup=INT_MAX;
    short ondeLer=1;
    Reg ultLido, registro;

    fseek(*arqLi, (Li-1)*sizeof(Reg), SEEK_SET);
    fseek(*arqEi, (Ei-1)*sizeof(Reg), SEEK_SET);

    *i=esq-1;
    *j=dir+1;

    comp++;
    while(Ls>=Li){
        comp+=8;
        if(nArea<TAM_AREA-1){
            if(ondeLer)
                leSup(arqLEs, &ultLido, &Ls, &ondeLer);
            else
                leInf(arqLi, &ultLido, &Li, &ondeLer);
            inserirArea(&area, &ultLido, &nArea);
            continue;
        }

        if(Ls == Es)
            leSup(arqLEs, &ultLido, &Ls, &ondeLer);
        else if(Li == Ei)
            leInf(arqLi, &ultLido, &Li, &ondeLer);
        else if(ondeLer)
            leSup(arqLEs, &ultLido, &Ls, &ondeLer);
        else
            leInf(arqLi, &ultLido, &Li, &ondeLer);

        if(ultLido.nota < lSup){
            *j=Es;
            escreveMax(arqLEs, ultLido, &Es);
            continue;
        }

        if(ultLido.nota > lInf){
            *i=Ei;
            escreveMin(arqEi, ultLido, &Ei);
            continue;
        }

        inserirArea(&area, &ultLido, &nArea);
        if(Ei-esq < dir-Es){
            retiraMin(&area, &registro, &nArea);
            escreveMin(arqEi, registro, &Ei);
            lInf = registro.nota;
        }
        else{
            retiraMax(&area, &registro, &nArea);
            escreveMax(arqLEs, registro, &Es);
            lSup = registro.nota;
        }
    }

    comp++;
    while(Ei <= Es){
        comp++;
        retiraMin(&area, &registro, &nArea);
        escreveMin(arqEi, registro, &Ei);
    }
}

void quickSort(unsigned long qnt){
    FILE *arqLEs;
    FILE *arqLi;
    FILE *arqEi;
    Reg r;

    arqLi = fopen("PROVAO.bin", "r+b");
    arqEi = fopen("PROVAO.bin", "r+b");
    arqLEs = fopen("PROVAO.bin", "r+b");

    comp++;
    if(arqEi==NULL || arqLi==NULL || arqLEs==NULL){
        printf("O arquivo nao pode ser aberto!\n");
        exit(1);
    }

    quickSortExt(&arqLi, &arqEi, &arqLEs, 1, qnt);

    fflush(arqLi); fflush(arqEi); fflush(arqLEs);
    fseek(arqLi, 0, SEEK_SET);

    //while(fread(&r, sizeof(Reg), 1, arqLi)){
    //    leituras++;
    //    printf("%-8ld %-5.2lf %-2s %-50s %-30s\n", r.matricula, r.nota, r.estado, r.cidade, r.curso);
    //}
    fclose(arqLi);
    bin_txt();
}

void FAVazia(TipoArea *area){
    int i;

    comp++;
    for(i=0; i<TAM_AREA; i++){
        comp++;
        area->regs[i].nota = -1;
    }
    area->celOcup=0;
}

void insereItem(Reg registro, TipoArea *area){
    Reg aux;
    int i=0;

    comp++;
    while(i<area->celOcup){
        comp+=2;
        if(registro.nota > area->regs[i].nota){
            aux = area->regs[i];
            area->regs[i] = registro;
            registro = aux;
        }
        i++;
    }
    area->regs[i] = registro;
    area->celOcup++;
}

int obterNumCelOcp(TipoArea *area){
    return area->celOcup;
}

void retiraUltimo(TipoArea *area, Reg *registro){
    area->celOcup--;
    *registro = area->regs[area->celOcup];
    area->regs[area->celOcup].nota = -1;
}

void retiraPrimeiro(TipoArea *area, Reg *registro){
    int i;

    area->celOcup--;
    *registro = area->regs[0];

    comp++;
    for(i=0; i<area->celOcup; i++){
        comp++;
        area->regs[i]=area->regs[i+1];
    }
}
