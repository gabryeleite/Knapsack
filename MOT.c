#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITEM 20
#define MAX_PESO 50
#define MAX_PRIORIDADE 100
#define CAPACIDADE 150

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
    int quant = rand() % MAX_ITEM + 1;
    int capacidade = rand() % CAPACIDADE + 1;
    Item *item = malloc(quant*sizeof(Item));

    for (int i = 0; i<quant; i++) {
        item[i].peso = rand() % MAX_PESO + 1;
        item[i].prioridade = rand() % 100 + 1;
    }

    PrintItem(item, capacidade, quant);

    printf("\n\nSolucao Obtida(MOT): %d\n\n", Mochila(capacidade, item, quant));

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
    for(int i=0; i<quant-1; i++){
        for(int j=0; j<quant-i-1; j++){
            if(item[j].peso <= item[j+1].peso){
                if(item[j].peso==item[j+1].peso && item[j].prioridade>=item[j+1].prioridade){
                    continue; 
                }else{
                    aux = item[j];
                    item[j] = item[j+1];
                    item[j+1] = aux; 
                }
            }
        }
    }
    printf("\nPesos Ordenados\n");
    for(int i=0; i<quant; i++) printf("%2d ", item[i].peso);
    printf("\n\nPrioridades Ordenadas\n");
    for(int i=0; i<quant; i++) printf("%2d ", item[i].prioridade);
}
int Mochila(int capacidade, Item *item, int quant){
    int totalpeso = 0;
    int totalprioridade = 0;

    Ordena(item, quant);

    for(int i=0; i<quant; i++){
        if(totalpeso + item[i].peso <= capacidade){
            totalpeso += item[i].peso;
            totalprioridade += item[i].prioridade;
        }
    }
    return totalprioridade;
}