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
int derrochandoEnergia = 0;

pthread_mutex_t cucharas[];

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
        pthread_mutex_init(&cucharas[i], NULL);
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

// El filosofo coge el tenedor, esta funcion obtiene el Nro del filosofo y el tenedor

void cogiendocucharas(int a, int b)
{
    pthread_mutex_lock(&cucharas[b]);
    printf("El filósofo número %d está usando el cucharas %d \n", a, b);
}

// El filosofo suelta el tenedor, esta funcion obtiene el numero del tenedor a dejar

void soltarcucharas(int s1, int s2)
{
    pthread_mutex_unlock(&cucharas[s1]);
    pthread_mutex_unlock(&cucharas[s2]);
}

// El filosofo piensa, esta funcion manda a pensar al filosofo

void piensa(int n)
{
    printf("Al Filosofo %d se le envio a pensar\n,", n);
    estomagos[n] -= 10;
    comio -= 10;
    derrochandoEnergia += 10;
    int aleatorio = rand() % 10;
    sleep(aleatorio);
}

// En esta función se halla la sección crítica

void comiendo(int arg)
{
    int t1 = arg - 2;
    int t2 = arg - 1;

    if (t1 == -1)
    {
        t1 = t2;
        t2 = numFilosofos - 1;
    }

    // Arreglando el deadlock

    if (arg == 1)
    {
        sleep(2);
    }

    cogiendocucharas(arg, t1);
    cogiendocucharas(arg, t2);

    printf("FILÓSOFO %d ESTA COMIENDO \n", arg);
    comida = comida - 250;
    estomagos[arg] += 250;
    comio += 2500;

    // Se verifica si los recursos deben restaurarse

    if (comida == 0 && comidaRestaurada > 0)
    {
        printf("TOTAL COMIDA EN ESTOMAGOS %d ... \n", comio);
        printf("TOTAL DE ENERGIA DERROCHADA %d ...\n", derrochandoEnergia);
        printf("LA CANTIDAD QUE SE COMIO %d ...\n", comio + derrochandoEnergia);

        comida = 3500;
        printf("YEY,COMIDA RESTAURADA \n");
    }

    printf("Verificando el estomago del filosofo %d: %d ... \n", arg, estomagos[arg]);
    printf("Cantidad de comida que queda: %d ... \n", comida);
    soltarcucharas(t1, t2);
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
