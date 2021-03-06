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
    int multiprocess;
    int multiprogram;
    int DeadlockDelay;
} t_kernelConfig;

t_kernelConfig* getKernelConfig(char* path);

void destroyKernelConfig(t_kernelConfig* config);

#endif // !KERNELCONFIG_H_

