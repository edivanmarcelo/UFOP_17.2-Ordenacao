#ifndef FITA_H_INCLUDED
#define FITA_H_INCLUDED
#include "Reg.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define TAM 20

void imprimiFin()	//IMPRIMI FITAS DE ENTRADA
{
	FILE *arq;

	char nome[20];
	int i, j;
	Reg reg;

	for(i = 1; i <= 20; i++)
	{
		sprintf(nome, "FITAIN%d.bin", i);

		if((arq = fopen(nome, "rb")) == NULL)
		{
			printf("ERRO NA ABERTURA DE ARQUIVO!\n");
			exit(1);
		}

		fseek(arq, 0, SEEK_END);
		long length = ftell(arq) / (sizeof(Reg));	//PEGA NUMERO DE REGISTROS NA FITA
		rewind(arq);

		if(length > 0)
		{
			if(i > 1) printf("\n\nFITAIN %d\n", i);
			else printf("FITAIN %d\n", i);
		}

		j = 0;
		while(fread(&reg, sizeof(Reg), 1, arq) == 1)
		{
			if(j % 20 == 0)	printf("\nBLOCO %d: ", j / 20 + 1);
			printf("%.2lf, ", reg.nota);
			j++;
		}

		fclose(arq);
	}

	printf("\n\n");
}

void imprimiFout()	//IMPRIMI FITAS DE SAIDA
{
	FILE *arq;

	char nome[20];
	int i, j;
	Reg reg;

	for(i = 1; i <= 20; i++)
	{
		sprintf(nome, "FITAOUT%d.bin", i);

		if((arq = fopen(nome, "rb")) == NULL)
		{
			printf("ERRO NA ABERTURA DE ARQUIVO!\n");
			exit(1);
		}

		fseek(arq, 0, SEEK_END);
		long length = ftell(arq) / (sizeof(Reg));	//PEGA NUMERO DE REGISTROS NA FITA
		rewind(arq);

		if(length > 0)
		{
			if(i > 1) printf("\n\nFITAOUT %d\n", i);
			else printf("FITAOUT %d\n", i);
		}

		j = 0;

		while(fread(&reg, sizeof(Reg), 1, arq) == 1)
		{
			if(j % 20 == 0)	printf("\n");
			printf("%.2lf, ", reg.nota);
			j++;
		}

		fclose(arq);
	}

	printf("\n\n");
}

void inicializa_fitaIn(int qt)	//CRIA FITAS DE ENTRADA
{
    FILE *arq;

    char nome[20];
    int i;
    Reg reg; comp++;

    for(i = 1; i <= qt; i++)
    {
        sprintf(nome, "FITAIN%d.bin", i);
        comp++;

        if((arq = fopen(nome, "wb")) == NULL)
        {
            printf("ERRO NA ABERTURA DE ARQUIVO!\n");
            exit(1);
        }

        comp++;

        fclose(arq);
    }
}

void inicializa_fitaOut(int qt)	//CRIA FITAS DE SAIDA
{
    FILE *arq;

    char nome[20];
    int i;
    Reg reg;

    comp++;
    for(i = 1; i <= qt; i++)
    {
        sprintf(nome, "FITAOUT%d.bin", i);
        comp++;

        if((arq = fopen(nome, "wb")) == NULL)
        {
            printf("ERRO NA ABERTURA DE ARQUIVO!\n");
            exit(1);
        }
        comp++;

        fclose(arq);
    }
}

void add_reg_fin(Reg reg, int n_fita)	//ADICIONA REGISTROS NA FITA DE ENTRADA
{
	FILE *arq;
	char nome[20];

	sprintf(nome, "FITAIN%d.bin", n_fita);
	comp++;

	if((arq = fopen(nome, "r+b")) == NULL)
	{
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		exit(1);
	}

	escritas++;
	fseek(arq, 0, SEEK_END);
	fwrite(&reg, sizeof(Reg), 1, arq);	//SALVA O REGISTRO NO ARQUIVO
	fclose(arq);
}

void arq_in_txt(int n_fita)	//CONVERTE ARQUIVO DE ENTRADA BINARIO PARA TXT
{
	FILE *leitura, *escrita; Reg reg;

	char nome[20];

	sprintf(nome, "FITAIN%d.bin", n_fita);

	if((leitura = fopen(nome, "rb")) == NULL)
	{
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		exit(1);
	}

	if((escrita = fopen("PROVAO_ORDENADO.txt", "w")) == NULL)
	{
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		exit(1);
	}

	char enter; int i = 0;

	while(fread(&reg, sizeof(Reg), 1, leitura) == 1)
	{
		fprintf(escrita, "%08ld %05.1f %2s %49s %29s\n", reg.matricula, reg.nota,
		                  reg.estado, reg.cidade, reg.curso);
		i++;
	}

	fclose(escrita);
	fclose(leitura);
}

void arq_out_txt(int n_fita)	//CONVERTE ARQUIVO DE SAIDA BINARIO PARA TXT
{
	FILE *leitura, *escrita; Reg reg;

	char nome[20];

	sprintf(nome, "FITAOUT%d.bin", n_fita);

	if((leitura = fopen(nome, "rb")) == NULL)
	{
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		exit(1);
	}

	if((escrita = fopen("PROVAO_ORDENADO.txt", "w")) == NULL)
	{
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		exit(1);
	}

	char enter; int i = 0; comp++;

	while(fread(&reg, sizeof(Reg), 1, leitura) == 1)
	{
		fprintf(escrita, "%08ld %05.1f %2s %49s %29s\n", reg.matricula, reg.nota,
		                  reg.estado, reg.cidade, reg.curso);
		i++;
	}

	fclose(escrita);
	fclose(leitura);
}

void atualizar_bloco_fin(Reg *reg, int tam, int n_fita, int n_bloco)	//ATUALIZA BLOCO DA FITA DE ENTRADA
{
	FILE *arq;

	char nome[20];

	sprintf(nome, "FITAIN%d.bin", n_fita);
	comp++;

	if((arq = fopen(nome, "r+b")) == NULL)
	{
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		exit(1);
	}

	escritas++;
	fseek(arq, (n_bloco - 1) * TAM * sizeof(Reg), SEEK_SET);
	fwrite(reg, sizeof(Reg), tam, arq);	//SALVA O BLOCO NO ARQUIVO
	fclose(arq);
}

void atualizar_bloco_fout(Reg *reg, int tam, int n_fita)	//ATUALIZA BLOCO DA FITA DE SAIDA
{
	FILE *arq;

	char nome[20];

	sprintf(nome, "FITAOUT%d.bin", n_fita);
	comp++;

	if((arq = fopen(nome, "r+b")) == NULL)
	{
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		exit(1);
	}

	escritas++;
	fwrite(reg, sizeof(Reg), tam, arq);	//SALVA O BLOCO NO ARQUIVO
	fclose(arq);
}

void add_reg_fout(Reg reg, int n_fita)	//ADICIONA REGISTRO NA FITA DE SAIDA
{
	FILE *arq;
	char nome[20];

	sprintf(nome, "FITAOUT%d.bin", n_fita);

	comp++;
	if((arq = fopen(nome, "r+b")) == NULL)
	{
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		exit(1);
	}

	escritas++;
	fseek(arq, 0, SEEK_END);
	fwrite(&reg, sizeof(Reg), 1, arq);	//SALVA O REGISTRO NO ARQUIVO
	fclose(arq);
}

Reg* get_last(int n_fita)	//RETORNA ULTIMO BLOCO DA FITA DE ENTRADA
{
	FILE *arq; Reg *reg;

	char nome[20];

	sprintf(nome, "FITAIN%d.bin", n_fita);
	comp++;

	if((arq = fopen(nome, "rb")) == NULL)
	{
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		exit(1);
	}

	fseek(arq, 0, SEEK_END);
	long length = ftell(arq) / (sizeof(Reg));	//PEGA NUMERO DE REGISTROS NA FITA

	comp++;
	if(length == 0) return NULL;
	comp++;
	if(length % TAM == 0){
		reg = malloc(sizeof(Reg) * TAM);
		fseek(arq, (length - TAM) * sizeof(Reg), SEEK_SET);	//POSICIONA O PONTEIRO NA POSIÇÃO N-20
		fread(reg, sizeof(Reg), TAM, arq);	leituras++;
		fclose(arq);
		return reg;
	}
	else{
		reg = malloc(sizeof(Reg) * (length % TAM));
		fseek(arq, (length - (length % TAM)) * sizeof(Reg), SEEK_SET);	//POSICIONA O PONTEIRO NA POSIÇÃO length - (length % TAM)
		fread(reg, sizeof(Reg), (length % TAM), arq);	leituras++;
		fclose(arq);
		return reg;
	}


}

int get_n_reg_in(int n_fita, int n_bloco, int n_reg, Reg *reg)	//PEGA REGISTRO N DA FITA DE ENTRADA
{
	FILE *arq; Reg aux;

	char nome[20];

	sprintf(nome, "FITAIN%d.bin", n_fita);
	comp++;

	if((arq = fopen(nome, "rb")) == NULL)
	{
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		exit(1);
	}

	fseek(arq, 0, SEEK_END);
	int length = ftell(arq) / (sizeof(Reg));	//PEGA NUMERO DE REGISTROS NA FITA

	comp++;
	if(length == 0){ fclose(arq); return 0;}	//SE NÃO HOUVER REGISTROS
	comp++;
	if(length % TAM == 0)
	{
		comp++;
		if(n_reg > TAM){ fclose(arq); return 0;}
		comp++;
		if(n_bloco > (length / TAM)){ fclose(arq); return 0;}//SE O BLOCO SOLICITADO FOR MAIOR QUE A QUANTIDADE TOTAL DE BLOCOS
	}
	else
	{
		int qt_blocos = (length / TAM) + 1;
		comp++;
		if(n_bloco > qt_blocos){ fclose(arq); return 0;}//SE O BLOCO SOLICITADO FOR MAIOR QUE A QUANTIDADE TOTAL DE BLOCOS
		comp++;
		if(n_bloco == qt_blocos)
		{
			comp++;
			if(n_reg > (length % TAM)){ fclose(arq); return 0;}	//SE O NUMERO DE REGISTROS FOR MAIOR QUE A QUANTIDADE DE REGISTROS NO BLOCO
		}
		else
		{
			comp++;
			if(n_reg > TAM){ fclose(arq); return 0;}	//SE O NUMERO DE REGISTROS FOR MAIOR QUE A QUANTIDADE DE REGISTROS NO BLOCO
		}
	}
	comp++;
	if(n_reg > TAM){ fclose(arq); return 0;}

	fseek(arq, ((n_bloco - 1) * TAM) * sizeof(Reg), SEEK_SET);	//POSICIONA O PONTEIRO NA POSIÇÃO n_bloco - 1 da fita
	fseek(arq, (n_reg - 1) * sizeof(Reg), SEEK_CUR);	//POSICIONA O PONTEIRO NA POSIÇÃO n_reg - 1 do bloco
	fread(&aux, sizeof(Reg), 1, arq);	//LE O REGISTRO
	leituras++;
	reg[n_fita-1] = aux;

	fclose(arq);
	return 1;
}

int get_n_reg_in1(int n_fita, int n_bloco, int n_reg, Reg *reg)	//SEGUNDA VERSAO EM CASO DE O NUMERO DE REGISTROS FOR MAIOR QUE 8.000
{
	FILE *arq; Reg aux;

	char nome[20];

	sprintf(nome, "FITAIN%d.bin", n_fita);
	comp++;
	if((arq = fopen(nome, "rb")) == NULL)
	{
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		exit(1);
	}

	comp++;
	if(n_fita == 1)
	{
		fseek(arq, 0, SEEK_END);
		int length = ftell(arq) / (sizeof(Reg));	//PEGA NUMERO DE REGISTROS NA FITA
		comp++;
		if(length == 0){ fclose(arq); return 0;}	//SE NÃO HOUVER REGISTROS
		comp++;
		if(n_reg > length){ fclose(arq); return 0;}	//SE O NUMERO DE REGISTROS FOR MAIOR QUE A QUANTIDADE DE REGISTROS NO BLOCO

		fseek(arq, ((n_bloco - 1) * TAM) * sizeof(Reg), SEEK_SET);	//POSICIONA O PONTEIRO NA POSIÇÃO n_bloco - 1 da fita
		fseek(arq, (n_reg - 1) * sizeof(Reg), SEEK_CUR);	//POSICIONA O PONTEIRO NA POSIÇÃO n_reg - 1 do bloco
		fread(&aux, sizeof(Reg), 1, arq);	//LE O REGISTRO
		leituras++;
		reg[n_fita-1] = aux;
	}

	else{
		fseek(arq, 0, SEEK_END);
		int length = ftell(arq) / (sizeof(Reg));	//PEGA NUMERO DE REGISTROS NA FITA

		comp++;
		if(length == 0){ fclose(arq); return 0;}	//SE NÃO HOUVER REGISTROS
		comp++;
		if(length % TAM == 0)
		{
			comp++;
			if(n_reg > TAM){ fclose(arq); return 0;}
			comp++;
			if(n_bloco > (length / TAM)){ fclose(arq); return 0;}//SE O BLOCO SOLICITADO FOR MAIOR QUE A QUANTIDADE TOTAL DE BLOCOS
		}
		else
		{
			int qt_blocos = (length / TAM) + 1;
			comp++;
			if(n_bloco > qt_blocos){ fclose(arq); return 0;}//SE O BLOCO SOLICITADO FOR MAIOR QUE A QUANTIDADE TOTAL DE BLOCOS
			comp++;
			if(n_bloco == qt_blocos)
			{
				comp++;
				if(n_reg > (length % TAM)){ fclose(arq); return 0;}	//SE O NUMERO DE REGISTROS FOR MAIOR QUE A QUANTIDADE DE REGISTROS NO BLOCO
			}
			else
			{
				comp++;
				if(n_reg > TAM){ fclose(arq); return 0;}	//SE O NUMERO DE REGISTROS FOR MAIOR QUE A QUANTIDADE DE REGISTROS NO BLOCO
			}
		}
		comp++;
		if(n_reg > TAM){ fclose(arq); return 0;}

		fseek(arq, ((n_bloco - 1) * TAM) * sizeof(Reg), SEEK_SET);	//POSICIONA O PONTEIRO NA POSIÇÃO n_bloco - 1 da fita
		fseek(arq, (n_reg - 1) * sizeof(Reg), SEEK_CUR);	//POSICIONA O PONTEIRO NA POSIÇÃO n_reg - 1 do bloco
		fread(&aux, sizeof(Reg), 1, arq);	//LE O REGISTRO
		leituras++;
		reg[n_fita-1] = aux;
	}
	fclose(arq);
	return 1;
}

int get_n_reg_out(int n_fita, int n_reg, Reg *reg)	//PEGA REGISTRO N DA FITA DE SAIDA
{
	FILE *arq; Reg aux;

	char nome[20];

	sprintf(nome, "FITAOUT%d.bin", n_fita);
	comp++;

	if((arq = fopen(nome, "r+b")) == NULL)
	{
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		exit(1);
	}

	fseek(arq, 0, SEEK_END);
	int length = ftell(arq) / (sizeof(Reg));	//PEGA NUMERO DE REGISTROS NA FITA

	comp++;
	if(n_reg > length || length == 0){ fclose(arq); return 0;}	//SE O NUMERO DE REGISTROS FOR MAIOR QUE A QUANTIDADE DE REGISTROS

	fseek(arq, (n_reg - 1) * sizeof(Reg), SEEK_SET);	//POSICIONA O PONTEIRO NA POSIÇÃO n_reg - 1 do bloco
	fread(&aux, sizeof(Reg), 1, arq);	//LE O REGISTRO
	reg[n_fita-1] = aux; leituras++;

	fclose(arq);
	return 1;
}

int qt_reg_bloco(int n_fita, int n_bloco)	//RETORNA QUANTIDADE DE REGISTRO NO BLOCO
{
	FILE *arq;

	char nome[20];

	sprintf(nome, "FITAIN%d.bin", n_fita);
	comp++;

	if((arq = fopen(nome, "rb")) == NULL)
	{
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		exit(1);
	}

	fseek(arq, 0, SEEK_END);
	int length = ftell(arq) / (sizeof(Reg));	//PEGA NUMERO DE REGISTROS NA FITA

	comp++;
	if(n_bloco > (length / TAM + 1) || length == 0){fclose(arq); return -1;}	//BLOCO NÃO EXISTE
	else if(n_bloco < (length / TAM + 1)){ fclose(arq); comp++; return TAM;}	//QUALQUER BLOCO QUE NÃO FOR O ULTIMO ESTARA COMPLETO
	comp+=2;
	if(length % TAM == 0){ fclose(arq); return TAM;}	//SE length % TAM == 0 ULTIMO BLOCO ESTÁ COMPLETO
	else { fclose(arq); return (length % TAM);} //SENÃO BLOCO ESTÁ INCOMPLETO

	fclose(arq);
}

void zerar_fita_in(int n_fita)	//APAGA FITA DE ENTRADA
{
	 FILE *arq;

	char nome[20];

	sprintf(nome, "FITAIN%d.bin", n_fita);
	comp++;

	if((arq = fopen(nome, "wb")) == NULL)
	{
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		exit(1);
	}

	fclose(arq);
}

void zerar_fita_out(int n_fita)	//APAGA FITA DE SAIDA
{
	 FILE *arq;

	char nome[20];

	sprintf(nome, "FITAOUT%d.bin", n_fita);
	comp++;

	if((arq = fopen(nome, "wb")) == NULL)
	{
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		exit(1);
	}

	fclose(arq);
}

int qt_blocos(int n_fita)	//RETORNA QUANTIDADE DE BLOCOS NA FITA DE ENTRADA
{
    FILE *arq;

    char nome[20];

    sprintf(nome, "FITAIN%d.bin", n_fita);
    comp++;

    if((arq = fopen(nome, "r+b")) == NULL)
    {
        printf("ERRO NA ABERTURA DE ARQUIVO!\n");
        exit(1);
    }

    fseek(arq, 0, SEEK_END);
	int length = ftell(arq) / (sizeof(Reg));	//PEGA NUMERO DE REGISTROS NA FITA
	fclose(arq);

	if(length % TAM == 0) return (length / TAM);
	else return (length / TAM) + 1;
}

#endif
