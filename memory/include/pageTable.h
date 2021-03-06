#include <stdint.h>
#include <stdbool.h>
#include <commons/collections/dictionary.h>
#include <pthread.h>

pthread_mutex_t pageTablesMut;
t_dictionary* pageTables;

typedef struct pageTableEntry {
    bool present;
    uint32_t frame;
} t_pageTableEntry;

typedef struct pageTable {
    int32_t pageQuantity;
    t_pageTableEntry *entries;
} t_pageTable;

t_pageTable *initializePageTable();

void destroyPageTable(t_pageTable *table);
void _destroyPageTable(void *table);

int32_t pageTableAddEntry(t_pageTable *table, uint32_t newFrame);

void pageTable_destroyLastEntry(t_pageTable* pt);

t_pageTable* getPageTable(uint32_t _PID, t_dictionary* pageTables);

bool pageTable_isEmpty(uint32_t PID);

int32_t pageTable_getFrame(uint32_t PID, uint32_t page);
