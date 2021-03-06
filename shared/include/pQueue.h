#ifndef PQUEUE_H_
#define PQUEUE_H_

#include <commons/collections/queue.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

/**
 * @DESC: Estructura FIFO con acceso protegido para multiples hilos.
 *        La cola esta equipada con un mutex para acceso individual,
 *        Y con un semaforo relativo a la cantidad de elementos.
 *        ideal para situaciones producer-consumer entre hilos.
 */
typedef struct pQueue{
    t_queue* elems;
    pthread_mutex_t mutex;
    sem_t sem;
} t_pQueue;

/**
 * @DESC: Crea una Cola de Procesos, protegida con mutex y semaforo
 * @return t_pQueue*: puntero a la cola protegida
 */
t_pQueue* pQueue_create();

/**
 * @DESC: Destruye una cola de procesos
 * @param queue: puntero a la cola a destruir
 */
void pQueue_destroy(t_pQueue* queue, void(*elemDestroyer)(void*));

/**
 * @DESC: Mete un proceso en una cola protegida
 * @param process: puntero al proceso
 * @param queue: puntero a la cola
 */
void pQueue_put(t_pQueue* queue, void* elem);

/**
 * @DESC: Saca un puntero de una cola protegida
 * @param queue: la cola
 * @return t_process*: puntero retornado
 */
void* pQueue_take(t_pQueue* queue);

/**
 * @DESC: Indica si una cola esta vacia
 * @param queue: cola a revisar
 * @return true: la cola esta vacia
 * @return false: la cola no esta vacia
 */
bool pQueue_isEmpty(t_pQueue* queue);

/**
 * @DESC: Itera una funcion sobre cada elemento de la cola
 * @param queue:
 * @param closure: funcion que modifica un elemento
 */
void pQueue_iterate(t_pQueue* queue, void(*closure)(void*));

/**
 * @DESC: Reordena una cola de procesos segun un algoritmo
 * @param queue: cola a ordenar
 * @param algorithm: algoritmo comparador, indica si el primer elemento va antes que el segundo
 */
void pQueue_sort(t_pQueue* queue, bool (*algorithm)(void*, void*));

/**
 * @DESC: Quita un elemento de la cola que cumpla la comparacion
 * @param queue:
 * @param comparison: funcion que evalue a true si se debe tomar el elemento
 */
void* pQueue_removeBy(t_pQueue* queue, bool (*condition)(void*));

/**
 * @DESC: Obtiene el mutex de la pQueue
 * @param queue:
 */
void pQueue_lock(t_pQueue* queue);

/**
 * @DESC: Libera el mutex de la pQueue
 * @param queue: 
 */
void pQueue_unlock(t_pQueue* queue);

/**
 * @DESC: Obtiene el ultimo elemento de la cola quitandolo
 * @param queue: 
 * @return void*: ultimo elemento de la lista
 */
void* pQueue_takeLast(t_pQueue* queue);

#endif // !PQUEUE_H_