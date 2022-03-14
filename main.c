#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arq.h"
#include "Ordenacao.h"
#include "Reg.h"
#include "Heap.h"
#include "OrdenacaoSS.h"
#include "ManipulaFitas.h"
#include "QuickSort.h"

int main(int argc, char *argv[])
{
	double tempof = 0; comp++;
	if(argc == 4 || argc == 5)
    {
        int metodo = atoi(argv[1]);
        unsigned long int quantidade = strtoul (argv[2], NULL, 0);
        int situacao = atoi(argv[3]);
        comp = escritas = leituras = 0; tempo = clock();
        switch(metodo)
        {
        case 1:
        	gerar_arq(situacao, quantidade);
        	comp+=2;
        	if(quantidade > 1)
        		ordena(metodo, quantidade);
        	else bin_txt();
			tempof = ((double) (clock() - tempo)) / (((double) CLOCKS_PER_SEC) / 1000);
			if(argc == 5 && ((strcmp(argv[4], "-p") == 0) || strcmp(argv[4], "-P") == 0))
			{
				imprimeProvao();
			}
        	break;

        case 2:
            gerar_arq(situacao, quantidade);
        	comp+=2;
            ordSubSel(quantidade);
            tempof = ((double) (clock() - tempo)) / (((double) CLOCKS_PER_SEC) / 1000);
            if(argc == 5 && ((strcmp(argv[4], "-p") == 0) || strcmp(argv[4], "-P") == 0))
				imprimeProvao();
            break;

        case 3:
            gerar_arq(situacao, quantidade);
            comp+=2;
            quickSort(quantidade);
            tempof = ((double) (clock() - tempo)) / (((double) CLOCKS_PER_SEC) / 1000);
            if(argc == 5 && ((strcmp(argv[4], "-p") == 0) || strcmp(argv[4], "-P") == 0))
				imprimeProvao();
            break;
        }
    }
    else
    {
        printf("ordena <metodo> <quantidade> <situacao> [-P]\n");
    }

	printf("Comparacoes: %lu\nLeituras: %lu\nEscritas: %lu\nTempo: %.2lf ms", comp, leituras, escritas, tempof);
}
