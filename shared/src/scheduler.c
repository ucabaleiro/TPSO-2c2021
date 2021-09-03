#include "scheduler.h"

t_processQueue* createProcessQueue(){
    t_processQueue* queue = malloc(sizeof(t_processQueue));
    queue->elems = queue_create();
    pthread_mutex_init(&queue->mutex, NULL);
    sem_init(&queue->sem, 0, 0);
    return queue;
}

void destroyProcessQueue(t_processQueue* queue){
    void _destroyProcess(void* process){
        void destroyProcess((t_process*)process);
    };
    queue_destroy_and_destroy_elements(queue->elems, _destroyProcess);
    pthread_mutex_destroy(&queue->mutex);
    sem_destroy(&queue->sem);
    free(queue);
}

t_process* createProcess(int id){
    t_process* process = malloc(sizeof(t_process));
    process->tasks = queue_create();
    process->pid = id;
    return process;
}

void destroyProcess(t_process* process){
    queue_destroy_and_destroy_elements(process->tasks, free);
    free(process);
}

void startScheduler(){
    new = createProcessQueue();
    ready = createProcessQueue();
    blocked = createProcessQueue();
    pthread_create(&thread_processInitializer, NULL, processInitializer, NULL);
    pthread_detach(&thread_processInitializer);
    pthread_create(&thread_executorIO, NULL, executorIO, NULL);
    pthread_detach(&thread_executorIO);
    for (int i = 0; i < MAX_MULTIPROCESSING; i++){
        pthread_create(&thread_executor[i], NULL, executor, NULL);
        pthread_detach(&thread_executor[i]);
    }
}

void* processInitializer(void* nada){
    while(1){
        t_process* process = takeProcess(new);
        //Realiza algun procesamiento...
        putProcess(process, ready);
    }
}

void* executor(void* nada){
    while(1){
        t_process* process = takeProcess(ready);
        int result = runCPU(process->tasks, QUANTUM);
        if(result == 0) putProcess(process, blocked);
        if(result == -1) destroyProcess(process);
        if(result == 1) putProcess(process, ready);
    }   
}

int runCPU(t_queue* tasks, int quantums){
    t_task* task = queue_peek(tasks);
    if(task == NULL) return -1;
    while(quantums){
        if(task->isIO) return 0;
        sleep(QUANTUM_LENGTH);
        task->remaining--;
        quantums--;
        if(task->remaining == 0){
            task = queue_pop(tasks); 
            free(task);
            task = queue_peek(tasks);
            if(task == NULL) return -1;
        }
    }
    return 1;
}

void* executorIO(void* nada){
    while(1){
        t_process* process = takeProcess(blocked);
        runIO(process->tasks);
        putProcess(process, ready);
    }
}

void runIO(t_queue* tasks){
    t_task* task = queue_peek(tasks);
    while(task->isIO){
        sleep(QUANTUM_LENGTH);
        task->remaining--;
        if(task->remaining == 0){
            task = queue_pop(tasks);
            free(task);
            task = queue_peek(tasks);
        }
    }
}

void putProcess(t_process* process, t_processQueue* queue){
    pthread_mutex_lock(&queue->mutex);
    queue_push(queue->elems, (void*)process);
    pthread_mutex_unlock(&queue->mutex);
    sem_post(&queue->sem);
}

t_process* takeProcess(t_processQueue* queue){
    sem_wait(&queue->sem);
    pthread_mutex_lock(&queue->mutex);
    t_process* process = queue_pop(queue->elems);
    pthread_mutex_unlock(&queue->mutex);
}