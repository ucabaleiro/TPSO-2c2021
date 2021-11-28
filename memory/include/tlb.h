#include<stdint.h>
#include<commons/collections/queue.h>
#include<commons/collections/dictionary.h>
#include<pthread.h>
#include<time.h>
#include<stdbool.h>
#include<stdio.h>


typedef struct tlbEntry {
    uint32_t pid;
    uint32_t page;
    int32_t frame;
    _Bool isFree;
    struct timespec* lastAccess;       //LRU
} t_tlbEntry;

typedef void (*TLBAlgorithm)(t_tlbEntry* newEntry);
typedef struct tlb {
    //Funcionamiento tlb
    t_tlbEntry* entries;
    unsigned int size;
    TLBAlgorithm replaceAlgorithm;
    t_queue* fifoEntries;
    pthread_mutex_t mutex;

    //Metricas
    t_dictionary* pidHits;
    t_dictionary* pidMisses;

} t_tlb;

t_tlb* tlb;

//Funciones
t_tlb* createTLB();
int32_t getFrameFromTLB(uint32_t pid, uint32_t page);
uint32_t addEntryToTLB(uint32_t pid, uint32_t page, int32_t frame);
void dropEntry(uint32_t pid, uint32_t page);
void destroyTLB(t_tlb* tlb);

//Metricas
void addToMetrics(t_dictionary* dic, uint32_t pid);
void sigIntHandlerTLB();
void printTlbHits(t_dictionary* hits);
void printTlbMisses(t_dictionary* misses);
void sigUsr1HandlerTLB();
void printTLBEntry(FILE* f, t_tlbEntry* entry, int nEntry);
void sigUsr2HandlerTLB();

//Algoritmos de reemplazo
void lruAlgorithm(t_tlbEntry* newEntry);
void fifoAlgorithm(t_tlbEntry* newEntry);