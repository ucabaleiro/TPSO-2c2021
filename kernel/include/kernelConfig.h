/**
 * @file: kernelConfig.h
 * @author pepinOS 
 * @DESC: TAD para un archivo de configuracion del Kernel
 * @version 0.1
 * @date: 2021-09-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef KERNELCONFIG_H_
#define KERNELCONFIG_H_

#include <commons/config.h>

typedef struct kernelConfig{
    t_config* config;
    char* kernelIP;
    char* kernelPort;
    char* memoryIP;
    char* memoryPort;
    char* schedulerAlgorithm;
    double initialEstimator;
    double alpha;
    char** IODeviceNames;
    char** IODeviceDelays;
    int CPUDelay;
    int multiprogram;
    int multiprocess;
} t_kernelConfig;

t_kernelConfig* getKernelConfig(char* path);

void destroyKernelConfig(t_kernelConfig* config);

#endif // !KERNELCONFIG_H_

