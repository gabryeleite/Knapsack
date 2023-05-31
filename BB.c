#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#define MAX_ITEM 1000
#define MAX_PESO 191
#define MAX_PRIORIDADE 91
#define CAPACIDADE 500

typedef struct{ //Linha 170: Comparar com SolOtima
    double fator;
    int prioridade;
    int peso;
    int qntpeso;
} Item;

void PrintItem(Item *item, int quant);
void Ordena(Item *item, int quant);
void AtribuiDado(Item *item, int quant);
int CalculaSol(Item *item, const int quantidades[]);
void AnalisaSol(Item *item, const int quantidades[], int MelhorSol[], int *SolAtual);
int IniciaRamo(Item *item, int quantidades[], int MelhorSol[], int *SolAtual);
void ReiniciaPoda(bool Poda[]);
int Limitante(Item *item, const int quantidades[], const int k);
bool AnalisaRamo(Item *item, const int quantidades[], bool Poda[], const int *SolAtual, const int k);
bool Ramifica(Item *item, int quantidades[], int *CapacRestante, int MelhorSol[], bool Poda[], int *SolAtual);
int Mochila(Item *item, int quantidades[]);

int main()
{
    srand(time(NULL));
    int quantidades[MAX_ITEM] = {0};
    Item *item = malloc(MAX_ITEM*sizeof(Item));

    AtribuiDado(item, MAX_ITEM);

    printf("\nBranch and Bound:\n");
    int solucao = Mochila(item, quantidades);

    printf("\nSolucao(BB): %d\n", solucao);

    free(item);
    
    return 0;
}

void Ordena(Item *item, int quant){
    Item aux;
    for(int i=0; i < quant-1; i++){
        for(int j=0; j < quant-i-1; j++){
            if(item[j].fator <= item[j+1].fator){
                if(item[j].fator==item[j+1].fator && item[j].peso<=item[j+1].peso){
                    continue; 
                }else{
                    aux = item[j];
                    item[j] = item[j+1];
                    item[j+1] = aux; 
                }
            }
        }
    }
}

void PrintItem(Item *item, int quant){
    printf("\niItens Ordenados: \n");
    for(int i=0; i<quant; i++){
        printf("Item: %2d\tPeso: %d\tPrioridade: %d\tFator: %.4f\n", i + 1, item[i].peso, item[i].prioridade, item[i].fator);
    }
}

void AtribuiDado(Item *item, int quant){
    for(int i=0; i < quant; i++) {
        item[i].peso = rand() % MAX_PESO + 10;
        item[i].prioridade = rand() % MAX_PRIORIDADE + 10;
    }
    for(int i=0; i < quant; i++){
        item[i].qntpeso = CAPACIDADE / item[i].peso;
        item[i].fator = (double)item[i].prioridade / item[i].peso;
    }
    Ordena(item, quant);

    PrintItem(item, quant);
}

int CalculaSol(Item *item, const int quantidades[]){
    int solucao = 0;
    for(int i=0; i < MAX_ITEM; i++){
        solucao += quantidades[i] * item[i].prioridade;
    }

    return solucao;
}

void AnalisaSol(Item *item, const int quantidades[], int MelhorSol[], int *SolAtual){
    int solucao = CalculaSol(item, quantidades);

    if(solucao > *SolAtual){
        for (int i=0; i < MAX_ITEM; i++){
            MelhorSol[i] = quantidades[i];
        }
        *SolAtual = solucao;
    }
}

int IniciaRamo(Item *item, int quantidades[], int MelhorSol[], int *SolAtual){
    int CapacRestante = CAPACIDADE;
    CapacRestante -= item[0].qntpeso * item[0].peso;
    quantidades[0] = item[0].qntpeso;

    for(int i=1; i < MAX_ITEM; i++){
        int qntde = CapacRestante / item[i].peso;
        quantidades[i] = qntde;
        CapacRestante -= qntde * item[i].peso;
    }

    *SolAtual = 0;
    AnalisaSol(item, quantidades, MelhorSol, SolAtual);

    return CapacRestante;
}

void ReiniciaPoda(bool Poda[]){
    for(int i=0; i < MAX_ITEM; i++){
        Poda[i] = false;
    }
}

int Limitante(Item *item, const int quantidades[], const int k){
    double limitante = 0;
    int somatorio = 0;

    for(int i=0; i < k; i++){
        limitante += item[i].prioridade * quantidades[i];
    }
    limitante += item[k].prioridade * (quantidades[k] - 1);

    for(int i=0; i < k; i++){
        somatorio += item[i].peso * quantidades[i];
    }
    limitante += item[k+1].fator * (CAPACIDADE - somatorio - item[k].peso * (quantidades[k] - 1));

    limitante = ceil(limitante);
    return (int)limitante;
}

bool AnalisaRamo(Item *item, const int quantidades[], bool Poda[], const int *SolAtual, const int k){
    int limitante = Limitante(item, quantidades, k);

    if(k==0){
        //Compara com a melhor solução atual
        if(limitante > *SolAtual){
            printf("%d > %d \n", limitante, *SolAtual);
            //Ramifica
            ReiniciaPoda(Poda);

            return true;
        }else{
            printf("%d < %d \nPoda\n", limitante, *SolAtual);
            //Poda
            Poda[k] = true;

            return false;
        }
    }else{
        //Compara com a solução ótima
        int SolOtima = CalculaSol(item, quantidades);
        if(limitante > *SolAtual){ 
            printf("%d > %d \n", limitante, SolOtima);
            //Ramifica
            ReiniciaPoda(Poda);

            return true;
        }else{
            printf("%d < %d \nPoda\n", limitante, SolOtima);
            //Poda
            Poda[k] = true;

            return false;
        }
    }
}

bool Ramifica(Item *item, int quantidades[], int *CapacRestante, int MelhorSol[], bool Poda[], int *SolAtual){
    int k = -1;

    for(int i = MAX_ITEM - 1; i >= 0; i--){
        if(quantidades[i] != 0 && Poda[i]==false){
            k = i;
            break;
        }
    }
    if(k==-1) return false;

    if(AnalisaRamo(item, quantidades, Poda, SolAtual, k)){
        quantidades[k] -= 1;
        *CapacRestante += item[k].peso;
        
        for(int i = k + 1; i < MAX_ITEM; i++){
            int qntde = (*CapacRestante) / item[i].peso;
            quantidades[i] = qntde;
            *CapacRestante -= qntde * item[i].peso;
        }
        AnalisaSol(item, quantidades, MelhorSol, SolAtual);
    }

    return true;
}

int Mochila(Item *item, int quantidades[]){
    int MelhorSol[MAX_ITEM], SolAtual = 0;
    bool Ramificacao = true;
    int CapacRestante = IniciaRamo(item, quantidades, MelhorSol, &SolAtual);

    bool Poda[MAX_ITEM];
    ReiniciaPoda(Poda);

    while (Ramificacao){
        Ramificacao = Ramifica(item, quantidades, &CapacRestante, MelhorSol, Poda, &SolAtual);
    }

    return SolAtual;
}