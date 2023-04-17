#include <iostream>
#include <vector>

#include <C:\Users\Piyush\Desktop\Programming\C++\College\sem4\operating_systems_lab\Process-Scheduling-Algos\objects\process\processes.h>

std::vector<Process *> processes;

inline void printProcesses() {for (auto i: processes) std::cout << i -> getId() << std::endl;}

void printTable() {
    std::cout << "PROCESS\tARRIVAL TIME\tBURST TIME\tCOMPLETION TIME\tTURNAROUND TIME\tWAIT TIME" << std::endl;
    for (auto i: processes) {
        std::cout << i -> getId() << "\t" << i -> getArrivalTime() << "\t\t" << i -> getBurstTime() << "\t\t" << i -> getCompletionTime() << "\t\t" << i -> getTurnAroundTime() << "\t\t" << i -> getWaitTime() << std::endl;
    }
}

Process::Process(int id, int aT, int bT)
    : id(id), arrivalTime(aT), burstTime(bT) {
    completionTime = 0;
    turnAroundTime = 0;
    waitTime = 0;
}

int Process::getId() {
    return id;
}

int Process::getArrivalTime() {
    return arrivalTime;
}

int Process::getBurstTime() {
    return burstTime;
}

int Process::getCompletionTime() {
    return completionTime;
}

int Process::getTurnAroundTime() {
    return turnAroundTime;
}

int Process::getWaitTime() {
    return waitTime;
}

void Process::setCompletionTime(int time) {
    this -> completionTime = time;
}

void Process::calculateTAT() {
    if (this -> completionTime == 0) {
        return;
    }

    this -> turnAroundTime = this -> completionTime - this -> arrivalTime;
}

void Process::calculateWT() {
    if (this -> turnAroundTime == 0) {
        return;
    }

    this -> waitTime = this -> turnAroundTime - this -> burstTime;
}