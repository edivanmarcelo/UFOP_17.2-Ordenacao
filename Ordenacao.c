#include "Ordenacao.h"
#include "Fita.h"
#include <math.h>
#include <float.h>
#include "Shell.h"

void ordena(int metodo, unsigned long qt)
{
	switch(metodo)
	{
	case 1:
		metodo1(qt);
		break;
	}

}

void metodo1(unsigned long qt)
{
	//GERACAO DOS BLOCOS

	inicializa_fitaIn(20);	//INICIALIZA 20 FITAS DE ENTRADA
	inicializa_fitaOut(20);	//INICIALIZA 20 FITAS DE SAIDA

	FILE *leitura; comp++;

	if((leitura = fopen("PROVAO.bin", "rb")) == NULL)
	{
		printf("ERRO NA ABERTURA DE ARQUIVO!\n");
		exit(1);
	}

	Reg reg, *aux = NULL;
	int n_fita = 1;
	int i = 1, n_bloco = 1, k = 0, j = 0, qualfita = 0;

	//PRIMEIRA FASE

	//CALCULA QUANTIDADE DE VEZES QUE O PROCESSO VAI REPETIR

	int vezes; comp++;
	if(qt > 8000) vezes = ceil((double) (qt - 8000) / 7600); else vezes = 0;

	do{
		//LE 8000 REGISTROS OU ATE O ARQUIVO ACABAR
		comp++;
		while(j < 8000 && fread(&reg, sizeof(Reg), 1, leitura) == 1)
		{
			leituras++;
			add_reg_fin(reg, n_fita);	//ADICIONA REGISTRO NA FITA DE ENTRADA
			comp++;

			if(i == TAM)	//SE O BLOCO ESTIVER CHEIO
			{
				aux = get_last(n_fita);	//ARMAZENO O ULTIMO BLOCO DA FITA
				shell_sort_invertido(aux, TAM);	//ORDENO
				atualizar_bloco_fin(aux, 20, n_fita, n_bloco);	//ATUALIZO NO ARQUIVO
				i=0;
				n_fita++;	//PULO DE FITA
				free(aux); aux = NULL;
			}

			comp++;

			if(n_fita == TAM+1)	//SE TODAS AS FITAS TIVEREM SIDO USADAS
			{
				comp++;
				//SE ESTIVER LENDO UM REGISTRO MAIOR QUE 8000 PRESERVO A FITA DE ENTRADA 1
				if(k > 0) n_fita = 2;
				else n_fita = 1;
				n_bloco++;	//PULO O BLOCO
			}

			i++; j++; comp++;
		}

		comp++;

		if(i > 2)	//SE TIVER PELO MENOS 2 REGISTROS NO ULTIMO BLOCO DA ULTIMA FITA LIDA
		{
			aux = get_last(n_fita);
			shell_sort_invertido(aux, i-1);
			atualizar_bloco_fin(aux, i-1, n_fita, n_bloco);
		}

		//SEGUNDA FASE

		//CALCULA NUMERO DE PASSADAS NA INTERCALACAO
		int passadas = (int) ceil((log((double) j/20) / log(20)));

		i = 0; comp++;

		while(i < passadas)
		{
			comp++;
			if(i % 2 == 0) {comp++; if(k==0)passada_fout(); else passada_fout1(); qualfita = 1;}
			else { passada_fin(); qualfita = 0;}
			i++; comp++;
		}

		k++, n_fita = 2, n_bloco = 1; i = 1; j = 400;
		int l = 1;
		comp++;

		//REINICIO DAS FITAS PRESERVANDO O ULTIMO BLOCO ORDENADO GERADO
		if(qualfita == 1)
		{
			comp++;
			while(l <= TAM)
			{
				comp+=2;
				zerar_fita_in(l);	//REINICIO AS FITAS DE ENTRADA
				l++;
				if(l <= TAM) zerar_fita_out(l);	//REINICIO AS FITAS DE SAIDA
			};
		}

		else
		{
			comp++;
			while(l <= TAM)
			{
				comp+=2;
				zerar_fita_out(l);	//REINICIO AS FITAS DE SAIDA
				l++;
				if(l <= TAM) zerar_fita_in(l);	//REINICIO AS FITAS DE ENTRADA
			};
		}

		comp++;
	}while(k <= vezes);

	comp++;
	if(qualfita == 0) arq_in_txt(1);	//RESULTADO DA INTERCALACAO CONVERTO PARA TXT
	else arq_out_txt(1);
	if(aux != NULL) free(aux);
	fclose(leitura);
}

void passada_fout1()	//INTERCALA REGISTROS DA FITA DE ENTRADA E JOGA NA FITA DE SAIDA
{
	int i = 0, n_fita = 1, n_bloco = 1;
	int n_reg[TAM];	//VETOR DE INT PARA GUARDAR A POSIÇÃO ATIVA DE CADA FITA
	Reg *aux = malloc(sizeof(Reg) * TAM);	//VETOR PARA GUARDAR REGISTRO ATIVO DE CADA FITA

	comp++;
	while(i < TAM){ comp++;	n_reg[i] = 1; aux[i].nota = 101; i++;}

	comp++;
	while(n_fita <= TAM)
	{
		comp+=2;
		if(get_n_reg_in1(n_fita, n_bloco, n_reg[n_fita-1], aux) == 0) n_reg[n_fita-1] = -1;	//FITA INATIVA
		n_fita++;
	}

	do{
		do
		{
			int qt_e = qt_enable(n_reg, 20);
			int j = 2, pos = first_enable(n_reg, 20); Reg aux1; aux1 = aux[pos-1]; comp++;

			while(j <= last_enable(n_reg, TAM))
			{
				if(isenable(n_reg[j-1]))
				{
					comp++;
					if(aux[j-1].nota > aux1.nota)	//VERIFICA A MAIOR NOTA
					{
						pos = j;
						aux1 = aux[j-1];
					}
				}
				j++; comp+=2;
			}

			add_reg_fout(aux1, n_bloco);

			n_reg[pos-1]++; comp+=2;
			if(get_n_reg_in1(pos, n_bloco, n_reg[pos-1], aux) == 0) n_reg[pos-1] = -1;	//FITA INATIVA
		}while(all_disable(n_reg, TAM) == 0);

		n_bloco++; i=1; n_fita=2; comp++;

		while(i < TAM){ comp++;	n_reg[i] = 1; aux[i].nota = 101; i++;}

		comp++;

		while(n_fita <= TAM)
		{
			comp+=2;
			if(get_n_reg_in1(n_fita, n_bloco, n_reg[n_fita-1], aux) == 0) n_reg[n_fita-1] = -1;	//FITA INATIVA
			n_fita++;
		}

		comp++;

	}while(all_disable(n_reg, TAM) == 0);
}

void passada_fout()	//INTERCALA REGISTROS DA FITA DE ENTRADA E JOGA NA FITA DE SAIDA
{
	int i = 0, n_fita = 1, n_bloco = 1;
	int n_reg[TAM];	//VETOR DE INT PARA GUARDAR A POSIÇÃO ATIVA DE CADA FITA
	Reg *aux = malloc(sizeof(Reg) * TAM);	//VETOR PARA GUARDAR REGISTRO ATIVO DE CADA FITA

	comp++;
	while(i < TAM){ comp++;	n_reg[i] = 1; aux[i].nota = 101; i++;}

	comp++;
	while(n_fita <= TAM)
	{
		if(get_n_reg_in(n_fita, n_bloco, n_reg[n_fita-1], aux) == 0) n_reg[n_fita-1] = -1;	//FITA INATIVA
		n_fita++; comp+=2;
	}

	do{
		do
		{
			int qt_e = qt_enable(n_reg, 20);
			int j = 2, pos = first_enable(n_reg, 20); Reg aux1; aux1 = aux[pos-1];

			while(j <= last_enable(n_reg, TAM))
			{
				if(isenable(n_reg[j-1]))
				{
					comp++;
					if(aux[j-1].nota > aux1.nota)	//VERIFICA A MENOR NOTA
					{
						pos = j;
						aux1 = aux[j-1];
					}
				}
				j++; comp+=2;
			}

			add_reg_fout(aux1, n_bloco);

			n_reg[pos-1]++; comp+=2;
			if(get_n_reg_in(pos, n_bloco, n_reg[pos-1], aux) == 0) n_reg[pos-1] = -1;	//FITA INATIVA
		}while(all_disable(n_reg, TAM) == 0);

		n_bloco++; i=0; n_fita=1; comp++;

		while(i < TAM){	comp++; n_reg[i] = 1; aux[i].nota = 101; i++;}

		comp++;
		while(n_fita <= TAM)
		{
			if(get_n_reg_in(n_fita, n_bloco, n_reg[n_fita-1], aux) == 0) n_reg[n_fita-1] = -1;	//FITA INATIVA
			n_fita++; comp+=2;
		}

		comp++;

	}while(all_disable(n_reg, TAM) == 0);
}

void passada_fin()	//INTERCALA REGISTROS DA FITA DE SAIDA E JOGA NA FITA DE ENTRADA
{
	remove("FITAIN1.bin");
	FILE *arq = fopen("FITAIN1.bin", "wb"); fclose(arq);
	int i = 0, n_fita = 1;
	int n_reg[TAM];	//VETOR DE INT PARA GUARDAR A POSIÇÃO ATIVA DE CADA FITA
	Reg *aux = malloc(sizeof(Reg) * TAM);	//VETOR PARA GUARDAR REGISTRO ATIVO DE CADA FITA

	comp++;
	while(i < TAM){	comp++; n_reg[i] = 1; aux[i].nota = 101; i++;}

	comp++;
	while(n_fita <= TAM)
	{
		if(get_n_reg_out(n_fita, n_reg[n_fita-1], aux) == 0) n_reg[n_fita-1] = -1;	//FITA INATIVA
		n_fita++; comp+=2;
	}

	n_fita = 1;

	do
	{
		int qt_e = qt_enable(n_reg, 20);
		int j = 2, pos = first_enable(n_reg, 20); Reg aux1; aux1 = aux[pos-1]; comp++;

		while(j <= last_enable(n_reg, TAM))
		{
			if(isenable(n_reg[j-1]))
			{
				comp++;
				if(aux[j-1].nota > aux1.nota)	//VERIFICA A MENOR NOTA
				{
					pos = j;
					aux1 = aux[j-1];
				}
			}
			j++; comp+=2;
		}

		add_reg_fin(aux1, n_fita);

		n_reg[pos-1]++; comp+=2;
		if(get_n_reg_out(pos, n_reg[pos-1], aux) == 0) n_reg[pos-1] = -1;	//FITA INATIVA
	}while(all_disable(n_reg, TAM) == 0);

	free(aux);
}

int isenable(int reg)	//SE A FITA ESTA ATIVA RETORNA 1
{
	comp++;
	return (reg != -1);
}

int first_enable(int n_reg[], int tam)	//RETORNA A PRIMEIRA FITA ATIVA
{
	int i = 1; comp++;

	while(i <= tam)
	{
		if(n_reg[i-1] != -1) return i;
		i++; comp+=2;
	}

	return i;
}

int last_enable(int n_reg[], int tam)	//RETORNA ULTIMA FITA ATIVA
{
	int i = 1, j = 1; comp++;

	while(i <= tam)
	{
		if(n_reg[i-1] != -1) j = i;
		i++; comp+=2;
	}

	return j;
}

int qt_enable(int n_reg[], int tam)	//RETORNA QUANTIDADE DE FITAS ATIVAS
{
	int i = 0, qt = 0; comp++;

	while(i < tam)
	{
		if(n_reg[i] != -1) qt++;
		i++; comp+=2;
	}

	return qt;
}

int all_disable(int n_reg[], int tam)	//RETORNA 1 CASO TODAS AS FITAS ESTEJAM INATIVAS
{
	int i = 0; comp++;

	while(i < tam)
	{
		if(n_reg[i] != -1) return 0;
		i++; comp+=2;
	}

	return 1;
}
