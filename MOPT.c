#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITEM 100
#define MAX_PESO 191
#define MAX_PRIORIDADE 91
#define CAPACIDADE 500

typedef struct{
    int peso;
    int prioridade;
    double fator;
} Item;

void AtribuiDado(Item *item, int quant);
void Ordena(Item *item, int quant);
void PrintItem(Item *item, int capacidade, int quant);
int Mochila(int capacidade, Item *item, int quant);

int main() 
{
    srand(time(NULL));
    int quant = MAX_ITEM;
    int capacidade = CAPACIDADE;
    Item *item = malloc(quant*sizeof(Item));

    AtribuiDado(item, quant);

    Ordena(item, quant);

    PrintItem(item, capacidade, quant);

    int solucao = Mochila(capacidade, item, quant);

    printf("\nSolucao Obtida(MOPT): %d\n\n", solucao);

    free(item);

    return 0;
}

void AtribuiDado(Item *item, int quant){
    for (int i = 0; i<quant; i++) {
        item[i].peso = rand() % MAX_PESO + 10;
        item[i].prioridade = rand() % MAX_PRIORIDADE + 10;
        item[i].fator = (double)item[i].prioridade / item[i].peso;
    }
}

void PrintItem(Item *item, int capacidade, int quant){
    printf("\nCAPACIDADE: %d\n", capacidade);
    printf("\nItens Ordenados pelo Fator:\n");
    for(int i=0; i<quant; i++){
        printf("Item: %2d\tPeso: %d\tPrioridade: %d\tFator: %.6lf\n", i + 1, item[i].peso, item[i].prioridade, item[i].fator);
    }
}

void Ordena(Item *item, int quant){
    Item aux;
    for(int i=0; i<quant-1; i++){
        for(int j=0; j<quant-i-1; j++){
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

int Mochila(int capacidade, Item *item, int quant){
    int totalpeso = 0;
    int totalprioridade = 0;
    int i = 0;

    while(i<quant){
        if(totalpeso + item[i].peso <= capacidade){
            totalpeso += item[i].peso;
            totalprioridade += item[i].prioridade;
        }else{
            i++;
        }
    }

    return totalprioridade;
}
