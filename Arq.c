#include "arq.h"
#include "Reg.h"
#include <stdio.h>

void txt_bin(unsigned long int qt)	//CONVERTE PROVAO.TXT PARA PROVAO.BIN
{
    FILE *leitura, *escrita;

    if((leitura = fopen("PROVAO.txt", "r")) == NULL)
    {
        printf("ERRO NA ABERTURA DE ARQUIVO!\n");
        exit(1);
    }

    if((escrita = fopen("PROVAO.bin", "wb")) == NULL)
    {
        printf("ERRO NA ABERTURA DE ARQUIVO!\n");
        exit(1);
    }

    Reg reg; char enter; unsigned long int i = 0;

    while (i < qt) {
        fscanf(leitura,"%ld %lf %s %49[A-Z a-z ' -] %[A-Z a-z] %[\n]", &reg.matricula, &reg.nota,
                  reg.estado, reg.cidade, reg.curso, enter);
        fwrite(&reg, sizeof(Reg), 1, escrita);
        i++;
    }

    fclose(escrita);
    fclose(leitura);
}

void bin_txt()	//CONVERTE PROVAO.BIN PARA PROVAO.TXT
{
    FILE *leitura, *escrita; comp++;

    if((leitura = fopen("PROVAO.bin", "rb")) == NULL)
    {
        printf("ERRO NA ABERTURA DE ARQUIVO!\n");
        exit(1);
    }

    if((escrita = fopen("PROVAO_ORDENADO.txt", "w")) == NULL)
    {
        printf("ERRO NA ABERTURA DE ARQUIVO!\n");
        exit(1);
    }

    Reg reg; char enter; int i = 0;

    while (fread(&reg, sizeof(Reg), 1, leitura)) {
        fprintf(escrita, "%08ld %05.1f %2s %49s %29s\n", reg.matricula, reg.nota,
                  reg.estado, reg.cidade, reg.curso);
        i++;
    }

    fclose(escrita);
    fclose(leitura);
}

void gerar_arq(int situacao, unsigned long int qt){	//GERA ARQUIVO BINARIO DE ACORDO COM A SITUACAO
    txt_bin(qt);

	switch(situacao)
	{
		case 1:
			ascendentemente(qt);
			break;
		case 2:
			descendentemente(qt);
			break;
		case 3:
			aleatorio(qt);
	}
}

//FUNCAO QUE GERA UM ARQUIVO COM A CHAVE GERADA ASCENDENTEMENTE
void ascendentemente(unsigned long int quant)
{
	FILE *escrita, *leitura;
	Reg *reg = malloc(sizeof(Reg) * quant);

	if((escrita = fopen("PROVAO-AUX.bin", "wb")) == NULL)
	{
		printf("Arquivo nao pode ser aberto");
		exit(1);
	}

	if((leitura = fopen("PROVAO.bin", "rb")) == NULL)
    {
        printf("Arquivo nao pode ser aberto");
		exit(1);
    }

    fread(reg, sizeof(Reg), quant, leitura);

    int i, j;
    Reg aux;

    if(quant > 1)
    	shell_sort(reg, quant);

    fwrite(reg, sizeof(Reg), quant, escrita);

    fclose(leitura);
    fclose(escrita);
    free(reg);
    remove("PROVAO.bin");
    rename("PROVAO-AUX.bin", "PROVAO.bin");
}

//FUNCAO QUE GERA UM ARQUIVO COM A CHAVE GERADA DESCENDENTEMENTE
void descendentemente(unsigned long int quant)
{
    FILE *escrita, *leitura;
	Reg *reg = malloc(sizeof(Reg) * quant);

	if((escrita = fopen("PROVAO-AUX.bin", "wb")) == NULL)
	{
		printf("Arquivo nao pode ser aberto");
		exit(1);
	}

	if((leitura = fopen("PROVAO.bin", "rb")) == NULL)
    {
        printf("Arquivo nao pode ser aberto");
		exit(1);
    }

    fread(reg, sizeof(Reg), quant, leitura);

    int i = 0, j = 0;
    Reg aux;

    if(quant > 1)
    	shell_sort_invertido(reg, quant);

    fwrite(reg, sizeof(Reg), quant, escrita);

    fclose(escrita);
	fclose(leitura);

    remove("PROVAO.bin");
    rename("PROVAO-AUX.bin", "PROVAO.bin");

}

void aleatorio(unsigned long int quant)
{
	FILE *escrita, *leitura;
	Reg *reg = malloc(sizeof(Reg) * quant);

	if((escrita = fopen("PROVAO-AUX.bin", "wb")) == NULL)
	{
		printf("Arquivo nao pode ser aberto");
		exit(1);
	}

	if((leitura = fopen("PROVAO.bin", "rb")) == NULL)
	{
		printf("Arquivo nao pode ser aberto");
		exit(1);
	}

	fread(reg, sizeof(Reg), quant, leitura);

	int i, j;
	Reg aux;

	fwrite(reg, sizeof(Reg), quant, escrita);

	fclose(leitura);
	fclose(escrita);
	free(reg);
	remove("PROVAO.bin");
	rename("PROVAO-AUX.bin", "PROVAO.bin");
}
