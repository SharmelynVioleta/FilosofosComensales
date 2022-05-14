#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *filosofo(void *arg);
int numFilosofos;
int comida = 3500;
int estomagos[];
int comio = 0;
int comidaRestaurada = 2;

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

void piensa(int n)
{
    printf("Al Filosofo %d se le envio a pensar\n,", n);

    int aleatorio = rand() % 10;
    sleep(aleatorio);
}

void comiendo(int arg)
{
    int t1 = arg - 2;
    int t2 = arg - 1;

    if (t1 == -1)
    {
        t1 = t2;
        t2 = numFilosofos - 1;
    }

    if (arg == 1)
    {
        sleep(2);
    }
    cogiendoTenedor(arg, t1);
    cogiendoTenedor(arg, t2);
    printf("FILÓSOFO %d ESTA COMIENDO \n", arg);
    comida = comida - 50;
    estomagos[arg] += 50;

    if (comida == 0 && comidaRestaurada > 0)
    {
        comida = 3500;
        printf("YEY,COMIDA RESTAURADA \n");
    }

    printf("Verificando el estomago del filosofo %d: %d ... \n", arg, estomagos[arg]);
    printf("Cantidad de comida que queda: %d ... \n", comida);
    soltarTenedor(t1, t2);
}

void *filosofo(void *arg)
{
    int arg2 = *((int *)arg);
    while (comida > 0)
    {
        piensa(arg2);
        comiendo(arg2);
    }
    return NULL;
}
