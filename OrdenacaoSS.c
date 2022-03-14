#include"ordenacaoSS.h"


void ordSubSel(unsigned long int qnt){
    criaFitas();
    FILE *leitura; //ARQUIVO PROVAO.bin
    Reg registro; //REGISTRO QUE SERA RETIRADO NO PROVAO.bin
    RegHeap novoReg; //NOVO REGISTRO QUE RECEBE O REGISTRO CONVERTIDO
    RegHeap auxReg; //VARIAVEL AUXILIAR PARA TROCAS DE REGISTROS
    RegHeap primReg; //VARIAVEL QUE GUARDA O VALOR DO PRIMEIRO REGISTRO DO HEAP
    RegHeap vetorHeap[MaxF/2]; //VETOR QUE CONSTITUI O HEAP
    FILE *fita; //VARIAVEL QUE RECEBE AS FITAS

    char nome[15]; //VARIAVEL QUE RECEBE O NOME DO ARQUIVO
    int nMaxH=0, nH=0; //VARIAVEL AUXILIARES QUE CONTROLAM O TAMANHO DO HEAP
    int saida=0; //GUARDA DA FITA SAIDA
    int entrada=0;//GUARDA DA FITA DE ENTRADA
    int qualFita=0;//GUARDA O VALOR DA FITA EM QUE O REGISTRO SERA ESCRITO
    int pos=1; //POSICAO DO REGISTRO NA FITA
    int i=0;
    int contFitas=2;

    leitura = fopen("PROVAO.bin", "rb");

    //DISTRIBUICAO DOS REGISTROS DO PROVAO ENTRE AS FITAS DE ENTRADA
    //CONSTRUCAO DO HEAP
    comp++;
    while(fread(&registro, sizeof(Reg), 1, leitura) == 1  && i<MaxF/2){
        converteReg(registro, &novoReg);
        vetorHeap[i] = novoReg;
        i++;
        leituras++;
        comp++;
    }
    heapConstroi(vetorHeap, i);
    fseek(leitura, i*sizeof(Reg), 0);

    nMaxH=i; nH=i; comp++;//INICIALIZACAO DAS FITAS
    while(nMaxH>0){ // PASSA OS REGISTROS DO PROVAO PARA AS FITAS DE ENTRADA
        primReg = vetorHeap[0];
        if(fread(&registro, sizeof(Reg), 1, leitura) != 1){// CONTROLADOR CASO O ARQ ESTEJA VAZIO OU
            vetorHeap[0] = vetorHeap[nH-1];                // O N MAXIMO DE RESGISTROS SEJA ATINGIDO
            vetorHeap[nH-1] = vetorHeap[nMaxH-1];
            nH--;nMaxH--;
        }
        else{
            leituras++;
            comp++;
            converteReg(registro, &novoReg);
            if(novoReg.nota > primReg.nota){//OPERACAO QUE BLOQUEIA O NOVO ELEMENTO CASO SEJA MAIOR QUE O QUE ESTA SAINDO
                vetorHeap[0] = vetorHeap[nH-1];
                vetorHeap[nH-1] = novoReg;
                nH--;
            }
            else
                vetorHeap[0] = novoReg;
        }

        primReg.origem = qualFita+1;//INICIALIZA A ORIGEM DO REGISTRO COM A FITA EM QUE SERA ESCRITO
        primReg.pos = pos; pos++;

        if(nH==0){ //DESBLOQUEIO DO HEAP
            nH=nMaxH;
            primReg.ultimo = 1;
            qualFita = (qualFita+1)%20;

            sprintf(nome, "fita%d.bin", qualFita+1);
            fita = fopen(nome, "r+b");
            fseek(fita, -(sizeof(RegHeap)), 2);
            comp++;
            if((fread(&novoReg, sizeof(RegHeap), 1, fita)) == 1){
                pos = novoReg.pos +1;
                leituras++;
            }
            else
                pos=1;
            fclose(fita);
        }

        sprintf(nome, "fita%d.bin", primReg.origem);//ESCRITA DO RESGISTRO NA FITA
        fita = fopen(nome, "r+b");
        fseek(fita, 0, 2);
        escritas++;
        fwrite(&primReg, sizeof(RegHeap), 1, fita);
        fclose(fita);
        heapConstroi(vetorHeap, nH);//RECONSTRUCAO DO HEAP
        comp+=3;
    }
    fclose(leitura);

    //INTECALACAO DOS REGISTROS ENTRE AS FITAS DE ENTRADA E AS FITAS DE SAIDA
    saida = 20;
    entrada = 0;
    int aux=2;
    while(aux > 1){//EXECUTA ENQUANTO AINDA HA MAIS DE UMA FITA COM REGISTROS
        contFitas = 0;
        pos = 1;
        qualFita = saida;
        comp+=2;

        for(i=1; i<=MaxF/2; i++){//PREENCHE O HEAP COM O PRIMEIRO REGISTRO DE CADA FITA DE ENTRADA
            comp+=2;
            sprintf(nome, "fita%d.bin", i+entrada);
            fita = fopen(nome, "r+b");
            if(fread(&novoReg, sizeof(RegHeap), 1, fita) == 1){
                leituras++;
                vetorHeap[contFitas] = novoReg;
                contFitas++;
            }
            fclose(fita);
            sprintf(nome, "fita%d.bin", i+saida);
            fita = fopen(nome, "wb");//LIMPA AS FITAS DE SAIDA
            fclose(fita);
        }

        aux=contFitas;
        if(aux > 1){
            heapConstroi(vetorHeap, contFitas);
            nH=contFitas; comp++;

            while(nH>0){
                comp+=3;
                primReg = vetorHeap[0];

                sprintf(nome, "fita%d.bin", primReg.origem);
                fita = fopen(nome, "r+b");
                fseek(fita, (primReg.pos*sizeof(RegHeap)), 0);

                if((fread(&novoReg, sizeof(RegHeap), 1, fita)) != 1){
                    vetorHeap[0] = vetorHeap[nH-1];
                    vetorHeap[nH-1] = vetorHeap[contFitas-1];
                    contFitas--;
                    nH--;
                }
                else if(primReg.ultimo == 1){
                    leituras++;
                    vetorHeap[0] = vetorHeap[nH-1];
                    vetorHeap[nH-1] = novoReg;
                    nH--;
                }
                else{
                    leituras++;
                    vetorHeap[0] = novoReg;
                }
                fclose(fita);

                primReg.origem = qualFita+1;
                primReg.pos = pos; pos++;
                comp++;
                if(nH==0){ //DESBLOQUEIO DO HEAP
                    nH = contFitas;
                    primReg.ultimo = 1;
                    qualFita = (qualFita+1)%20 + saida;

                    sprintf(nome, "fita%d.bin", qualFita+1);
                    fita = fopen(nome, "r+b");
                    fseek(fita, -(sizeof(RegHeap)), 2);
                    comp++;
                    if((fread(&novoReg, sizeof(RegHeap), 1, fita)) == 1){
                        pos = novoReg.pos +1;
                        leituras++;
                    }
                    else
                        pos=1;
                    fclose(fita);
                }
                else{
                    primReg.ultimo = 0;
                }

                sprintf(nome, "fita%d.bin", primReg.origem);//ESCRITA DO RESGISTRO NA FITA
                fita = fopen(nome, "r+b");
                fseek(fita, 0, 2);
                escritas++;
                fwrite(&primReg, sizeof(RegHeap), 1, fita);
                fclose(fita);
                heapConstroi(vetorHeap, nH);//RECONSTRUCAO DO HEAP
                comp++;
            }
        }
        i = entrada;
        entrada = saida;
        saida = i;
    }

    converteProvao(vetorHeap[0]);
}
