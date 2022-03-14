#include "Shell.h"
#include "Reg.h"
#include <stdlib.h>

void shell_sort(Reg vet[], int n){
    int i, j, h;
    Reg aux;

    for(h = 1; h < n; h = 3 * h + 1, comp++);

    do{
        h = (h - 1) / 3;
        for(i = h; i < n; i++){
            aux = vet[i];
            j = i;
            comp++;
            while (vet[j - h].nota > aux.nota){
                comp+=2;
                vet[j] = vet[j - h];
                j -= h;
                if (j < h) break;
            }
            vet[j] = aux;

        }
        comp++;
    } while (h != 1);
}

void shell_sort_invertido(Reg *vet, int n){
    int i, j, h;
    Reg aux;

    for(h = 1; h < n; h = 3 * h + 1);

    do{
        h = (h - 1) / 3;
        for(i = h; i < n; i++){
            aux = vet[i];
            j = i;
            comp++;
            while (vet[j - h].nota <= aux.nota){
                comp+=2;
                vet[j] = vet[j - h];
                j -= h;
                if (j < h) break;
            }
            vet[j] = aux;
        }
    } while (h != 1);
}
