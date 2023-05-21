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
} Item;

void PrintItem(Item *item, int capacidade, int quant);
void Ordena(Item *item, int quant);
int Mochila(int capacidade, Item *item, int quant);

int main() 
{
    srand(time(NULL));
    int quant = MAX_ITEM;
    int capacidade = CAPACIDADE;
    Item *item = malloc(quant*sizeof(Item));

    for (int i = 0; i<quant; i++) {
        item[i].peso = rand() % MAX_PESO + 11;
        item[i].prioridade = rand() % MAX_PRIORIDADE + 11;
    }

    PrintItem(item, capacidade, quant);

    printf("\n\nSolucao Obtida(MOPT): %d\n\n", Mochila(capacidade, item, quant));

    free(item);
    return 0;
}
void PrintItem(Item *item, int capacidade, int quant){
    printf("\nCAPACIDADE: %d\n", capacidade);
    printf("\nITENS:\n");
    for(int i=0; i<quant; i++){
        printf("Item: %2d\tPeso: %2d\tPrioridade: %2d\n", i + 1, item[i].peso, item[i].prioridade);
    }
}
void Ordena(Item *item, int quant){
    Item aux;
    double fator[2];
    for(int i=0; i<quant-1; i++){
        for(int j=0; j<quant-i-1; j++){
            fator[0] = (double)item[j].prioridade/item[j].peso;
            fator[1] = (double)item[j+1].prioridade/item[j+1].peso;
            if(fator[0] <= fator[1]){
                if(fator[0]==fator[1] && item[j].peso<=item[j+1].peso){
                    continue; 
                }else{
                    aux = item[j];
                    item[j] = item[j+1];
                    item[j+1] = aux; 
                }
            }
        }
    }
    printf("\nFator Ordenado(prioridade/peso):\n");
    for(int i=0; i<quant; i++) printf("%.4f ", (float)item[i].prioridade/item[i].peso);
    printf("\n\nPesos Ordenados(Em relacao ao fator):\n");
    for(int i=0; i<quant; i++) printf("%d ", item[i].peso);
    printf("\n\nPrioridades Ordenadas(Em relacao ao fator):\n");
    for(int i=0; i<quant; i++) printf("%d ", item[i].prioridade);
}
int Mochila(int capacidade, Item *item, int quant){
    int totalpeso = 0;
    int totalprioridade = 0;
    int i = 0;

    Ordena(item, quant);

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
