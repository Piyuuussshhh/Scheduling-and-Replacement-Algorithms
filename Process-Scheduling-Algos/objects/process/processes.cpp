#include <iostream>

#include <../Process-Scheduling-Algos/objects/process/processes.h>

int Process::getArrivalTime() {
    return arrivalTime;
}

int Process::getBurstTime() {
    return burstTime;
}

int Process::getCompletionTime() {
    return completionTime;
}