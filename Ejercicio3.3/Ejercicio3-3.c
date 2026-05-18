#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

// Variable compartida entre los hilos
int a = 0;

// Número de veces que se ejecutará cada hilo
long MAX = 5;

// Declaración de funciones de los hilos
void * funcion_hilo1(void *arg);
void * funcion_hilo2(void *arg);
void * funcion_hilo3(void *arg);

// Semáforo global
sem_t s;

int main(void){

    // Declaración de los 3 hilos
    pthread_t hilo1, hilo2, hilo3;

    // Inicialización del semáforo
    // 0 = compartido entre hilos del mismo proceso
    // 1 = valor inicial del semáforo
    sem_init(&s, 0, 1);

    // Creación de los hilos
    pthread_create(&hilo1, NULL, *funcion_hilo1, NULL);
    pthread_create(&hilo2, NULL, *funcion_hilo2, NULL);
    pthread_create(&hilo3, NULL, *funcion_hilo3, NULL);

    // Espera a que terminen los hilos
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_join(hilo3, NULL);

    // Mostrar valor final de la variable compartida
    printf("El valor de a es %d\n", a);

    // Destruir el semáforo
    sem_destroy(&s);

    return 0;
}

// ====================== HILO 1 ======================
void * funcion_hilo1(void *arg){

    int val_semaforo;

    for (int i = 0; i < MAX; i++){

        // Entra a la sección crítica
        sem_wait(&s);

        // Obtiene el valor actual del semáforo
        sem_getvalue(&s, &val_semaforo);

        printf(
            "Hilo[1] En seccion critica. Valor semaforo: %d | a previo = %d ",
            val_semaforo,
            a
        );

        // Modifica la variable compartida
        a += 1;

        printf("a actual = %d\n", a);

        // Libera la sección crítica
        sem_post(&s);
    }
}

// ====================== HILO 2 ======================
void * funcion_hilo2(void *arg){

    int val_semaforo;

    for (int i = 0; i < MAX; i++){

        // Bloquea acceso a otros hilos
        sem_wait(&s);

        // Consulta el valor del semáforo
        sem_getvalue(&s, &val_semaforo);

        printf(
            "Hilo[2] En seccion critica. Valor semaforo: %d | a previo = %d ",
            val_semaforo,
            a
        );

        // Resta 1 a la variable compartida
        a -= 1;

        printf("a actual = %d\n", a);

        // Libera el semáforo
        sem_post(&s);
    }
}

// ====================== HILO 3 ======================
void * funcion_hilo3(void *arg){

    int val_semaforo;

    for (int i = 0; i < MAX; i++){

        // Entrada a sección crítica
        sem_wait(&s);

        // Obtener valor actual del semáforo
        sem_getvalue(&s, &val_semaforo);

        printf(
            "Hilo[3] En seccion critica. Valor semaforo: %d | a previo = %d ",
            val_semaforo,
            a
        );

        // Incrementa en 2 la variable compartida
        a += 2;

        printf("a actual = %d\n", a);

        // Sale de la sección crítica
        sem_post(&s);
    }
}