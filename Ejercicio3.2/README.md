### 2. Hilos con Sincronización (Semáforos POSIX)

Resultados tras proteger la sección crítica con `sem_wait` y `sem_post`:

| Valor de `MAX` | Valor de la variable `a` impreso |
| :--- | :--- |
| **1 000 000** | 0 |
| **1e9** | 0 |
| **1e12** | No finaliza / Tiempo de ejecución excesivo |

#### ¿Por qué sale esto?
* **Resultados en 0:** Los semáforos garantizan la exclusión mutua. Solo un hilo puede entrar a modificar la variable `a` a la vez; si el otro intenta entrar, se va a una cola de espera. Se elimina la condición de carrera y el resultado siempre es determinista
* **Se frena en 1e12:** El programa se queda congelado por el **overhead de sincronización**. Bloquear, verificar la llave en memoria y desbloquear el semáforo un billón de veces obliga al procesador a ir estrictamente en fila india. Esto destruye el paralelismo y hace que tarde horas en terminar, demostrando que asegurar los datos cuesta rendimiento.
