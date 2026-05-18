#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Declaración del mutex
pthread_mutex_t mutex;

// Variable global compartida
char *color;

// Hilo rojo
void * rojo(void *arg){

    // Bloquea el mutex
    // Solo un hilo puede entrar aquí a la vez
    pthread_mutex_lock(&mutex);

    // Código ANSI para color rojo
    color = "\x1b[31m";

    // Cambia color del texto
    printf("%s", color);

    // Imprime mensaje en rojo
    printf("Este texto es color ROJO!\n");

    // Libera el mutex
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Hilo verde
void * verde(void *arg){

    // Bloquea acceso a la sección crítica
    pthread_mutex_lock(&mutex);

    // Código ANSI para color verde
    color = "\x1b[32m";

    // Cambia color del texto
    printf("%s", color);

    // Mensaje en verde
    printf("Este texto es color VERDE!\n");

    // Desbloquea el mutex
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Hilo azul
void * azul(void *arg){

    // Entrada a sección crítica
    pthread_mutex_lock(&mutex);

    // Código ANSI para color azul
    color = "\x1b[34m";

    // Aplicar color
    printf("%s", color);

    // Mostrar mensaje azul
    printf("Este texto es color AZUL!\n");

    // Libera el mutex
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(void){

    // Inicialización del mutex
    pthread_mutex_init(&mutex, NULL);

    // Declaración de hilos
    pthread_t hilo1, hilo2, hilo3;

    // Creación de hilos
    pthread_create(&hilo1, NULL, *rojo, NULL);
    pthread_create(&hilo2, NULL, *verde, NULL);
    pthread_create(&hilo3, NULL, *azul, NULL);

    // Esperar a que terminen los hilos
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_join(hilo3, NULL);

    // Destruir mutex al finalizar
    pthread_mutex_destroy(&mutex);

    return 0;
}