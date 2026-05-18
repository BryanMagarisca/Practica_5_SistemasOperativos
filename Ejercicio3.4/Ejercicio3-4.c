#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// Declaración del semáforo
sem_t s;

// Variable global para almacenar el color
char *color;

// Hilo Rojo
void * rojo(void *arg){

    // Bloquea acceso a la sección crítica
    sem_wait(&s);

    // Código ANSI para color rojo
    color = "\x1b[31m";

    // Cambia color del texto en consola
    printf("%s", color);

    // Mensaje en rojo
    printf("Este texto es ROJO!\n");

    // Libera el semáforo
    sem_post(&s);

    return NULL;
}

//Hilo verde
void * verde(void *arg){

    // Entrada a sección crítica
    sem_wait(&s);

    // Código ANSI para color verde
    color = "\x1b[32m";

    // Aplicar color
    printf("%s", color);

    // Mostrar mensaje
    printf("Este texto es VERDE!\n");

    // Libera el recurso compartido
    sem_post(&s);

    return NULL;
}

//Hilo azul
void * azul(void *arg){

    // Bloquea acceso simultáneo
    sem_wait(&s);

    // Código ANSI para color azul
    color = "\x1b[34m";

    // Cambia color de salida
    printf("%s", color);

    // Imprime texto azul
    printf("Este texto es AZUL!\n");

    // Libera el semáforo
    sem_post(&s);

    return NULL;
}

int main(void){

    // Inicializa el semáforo
    // Valor inicial = 1
    sem_init(&s, 0, 1);

    // Declaración de hilos
    pthread_t hilo_rojo, hilo_verde, hilo_azul;

    // Creación de hilos
    pthread_create(&hilo_rojo, NULL, *rojo, NULL);
    pthread_create(&hilo_verde, NULL, *verde, NULL);
    pthread_create(&hilo_azul, NULL, *azul, NULL);

    // Espera a que terminen los hilos
    pthread_join(hilo_rojo, NULL);
    pthread_join(hilo_verde, NULL);
    pthread_join(hilo_azul, NULL);

    return 0;
}