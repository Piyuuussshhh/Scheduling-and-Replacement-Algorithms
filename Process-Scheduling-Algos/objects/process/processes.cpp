#include <iostream>
#include <vector>

#include <C:\Users\Piyush\Desktop\Programming\C++\College\sem4\operating_systems_lab\Process-Scheduling-Algos\objects\process\processes.h>

std::vector<Process *> processes;

inline void printProcesses() {for (auto i: processes) std::cout << i -> getId() << std::endl;}

void printTable(std::vector<Process *> p = processes) {
    std::cout << "PRIORITY\tPROCESS\t\tARRIVAL TIME\tBURST TIME\tCOMPLETION TIME\tTURNAROUND TIME\tWAIT TIME" << std::endl;
    for (auto i: p) {
        std::cout << i -> getPriority() << "\t\t" << i -> getId() << "\t\t" << i -> getArrivalTime() << "\t\t" << i -> getBurstTime() << "\t\t" << i -> getCompletionTime() << "\t\t" << i -> getTurnAroundTime() << "\t\t" << i -> getWaitTime() << std::endl;
    }
}

Process::Process(int id, int aT, int bT)
    : id(id), arrivalTime(aT), burstTime(bT) {
    completionTime = 0;
    turnAroundTime = 0;
    waitTime = 0;
    priority = 0;
}

Process::Process(int id, int aT, int bT, int priority)
    : id(id), arrivalTime(aT), burstTime(bT), priority(priority) {
    completionTime = 0;
    turnAroundTime = 0;
    waitTime = 0;
}

bool Process::operator ==(Process *p2) {
    if (this -> id == p2 -> id) {
        return true;
    }
    return false;
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

int Process::getPriority() {
    return priority;
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