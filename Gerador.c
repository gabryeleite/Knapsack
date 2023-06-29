#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITEM 100
#define MAX_PESO 191
#define MAX_PRIORIDADE 91

typedef struct{
    int peso;
    int prioridade;
} Item;

int main()
{
    srand(time(NULL));

    for(int j=0; j < 100; j++)
    {
        Item *item = malloc(MAX_ITEM * sizeof(Item));
        FILE *file = fopen("nome.txt","a");

        for(int i = 0; i < MAX_ITEM; i++) {
            item[i].peso = rand() % MAX_PESO + 10;
            item[i].prioridade = rand() % MAX_PRIORIDADE + 10;
            fprintf(file, "%d %d\n", item[i].peso, item[i].prioridade);
        }
        fclose(file);

        free(item);
    }
    printf("Arquivo criado com sucesso!\n");

    return 0;
}
