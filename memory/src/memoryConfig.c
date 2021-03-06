#include "memoryConfig.h"
#include <stdlib.h>

t_memoryConfig *getMemoryConfig(char *path){
    t_memoryConfig *memConfig = malloc(sizeof(t_memoryConfig));
    memConfig-> config = config_create(path);

    // Networking
    memConfig -> swapIP = config_get_string_value(memConfig->config, "IP_SWAP");
    memConfig -> swapPort = config_get_string_value(memConfig->config, "PUERTO_SWAP");
    memConfig -> ip = config_get_string_value(memConfig-> config, "IP");
    memConfig -> port = config_get_string_value(memConfig-> config, "PUERTO");
    

    memConfig -> size = config_get_int_value(memConfig-> config, "TAMANIO");
    memConfig -> pageSize = config_get_int_value(memConfig-> config, "TAMANIO_PAGINA");
    memConfig -> MMUreplacementAlgorithm = config_get_string_value(memConfig-> config, "ALGORITMO_REEMPLAZO_MMU");
    memConfig -> assignmentType = config_get_string_value(memConfig-> config, "TIPO_ASIGNACION");
    memConfig -> framesPerProcess = config_get_int_value(memConfig-> config, "MARCOS_POR_PROCESO");
    memConfig -> frameQty = memConfig->size / memConfig->pageSize;

    // TLB
    memConfig -> TLBEntryAmount = config_get_int_value(memConfig-> config, "CANTIDAD_ENTRADAS_TLB");
    memConfig -> TLBReplacementAlgorithm = config_get_string_value(memConfig-> config, "ALGORITMO_REEMPLAZO_TLB");
    memConfig -> TLBHitDelay = config_get_int_value(memConfig-> config, "RETARDO_ACIERTO_TLB");
    memConfig -> TLBMissDelay = config_get_int_value(memConfig-> config, "RETARDO_FALLO_TLB");
    memConfig -> TLBPathDump = config_get_string_value(memConfig-> config, "DUMP_PATH");

    return memConfig;
}   

void destroyMemoryConfig(t_memoryConfig *config){
    free(config -> swapIP);
    free(config -> swapPort);
    free(config -> ip);
    free(config -> port);
    free(config -> MMUreplacementAlgorithm);
    free(config -> assignmentType);
    free(config -> TLBReplacementAlgorithm);
    free(config -> TLBPathDump);
    config_destroy(config->config);
    free(config);
}

void validateConfg(t_memoryConfig *config, t_log *logger){
    if(config->size % config->pageSize != 0) {
        log_error(logger, "Configuracion incorrecta: el tamanio total no es multiplo del tamanio de pagina.");
        exit(EXIT_FAILURE);
    }
}