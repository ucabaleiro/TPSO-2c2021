#include "process.h"
#include <stdlib.h>
#include <unistd.h>

t_process* createProcess(int id, int socket, double estimate){
    t_process* process = malloc(sizeof(t_process));
    process->pid = id;
    process->socket = socket;
    process->state = NEW;
    process->estimate = estimate;
    process->waitedTime = 0;
    process->inited = false;
    return process;
}

void destroyProcess(t_process* process){
    close(process->socket);
    free(process);
}

