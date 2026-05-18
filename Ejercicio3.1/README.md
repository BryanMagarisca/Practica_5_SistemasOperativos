

## Tablas de Datos y Análisis

### 1. Hilos sin Sincronización 

Resultados al correr los hilos modificando la variable global `a`, sin semáforos ni exclusión mutua:

<img width="261" height="151" alt="image" src="https://github.com/user-attachments/assets/8dcc6bd8-0d38-4aa2-a701-c38f7b29bb5a" />

#### ¿Por qué sale esto?
* **Valores bajos (1 000 a 100 000):** Da `0` porque el procesador los corre tan rápido que un hilo termina todo su bucle antes de que el sistema operativo haga el cambio de contexto, al ejecutarse uno primero y el otro después, no chocan
* **Valor en 1 000 000:** Al subir las iteraciones, el tiempo supera el *quantum* del sistema operativo, el planificador empieza a intercalar los hilos a nivel de hardware y, como ambos entran a la sección crítica a la vez sin control, se sobreescriben la memoria mutuamente. Se pierden datos y por eso el resultado es caótico y cambia en cada ejecución

---
