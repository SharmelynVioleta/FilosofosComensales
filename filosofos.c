#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int numFilosofos;

void *filosofo(void *arg);
int var = 0;

pthread_mutex_t tenedor[5];

int main(void)
{
    printf("Iniciando programa de filosofos COmensales\n");
    printf("\tFILÓSOFOS:\n");
    printf("Ingrese el numero de filosofos: ");
    scanf("%d", &numFilosofos);
    pthread_t filosofos[numFilosofos];
    int id[numFilosofos];
    int i;

    for (int i = 0; i < numFilosofos; i++)
    {
        pthread_mutex_init(&tenedor[i], NULL);
    }
    for (int i = 0; i < numFilosofos; i++)
    {
        id[i] = i + 1;
        pthread_create(&filosofos[i], NULL, &filosofo, &id[i]);
    }
    for (int i = 0; i < numFilosofos; i++)
    {
        pthread_join(filosofos[i], NULL);
    }

    return 0;
}
void cogiendoTenedor(int a, int b)
{
    pthread_mutex_lock(&tenedor[b]);
    printf("El filósofo número %d está usando el tenedor %d \n", a, b);
}

void soltarTenedor(int s1, int s2)
{
    pthread_mutex_unlock(&tenedor[s1]);
    pthread_mutex_unlock(&tenedor[s2]);
}

void comiendo(int arg)
{
    int t1 = arg - 1;
    int t2 = arg - 2;
    if (t2 == -1)
    {
        t2 = 4;
    }
    if (arg == 1)
    {
        sleep(2);
    }
    cogiendoTenedor(arg, t1);
    cogiendoTenedor(arg, t2);
    printf("FILÓSOFO %d ESTA COMIENDO \n", arg);
}
void *filosofo(void *arg)
{
    int arg2 = *((int *)arg);
    for (int i = 1; i <= 5; i++)
    {
        var = var + 1;
        comiendo(arg2);
    }
    return NULL;
}
