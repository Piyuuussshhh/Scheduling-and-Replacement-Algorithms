#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

#include <C:\Users\Piyush\Desktop\Programming\C++\College\sem4\operating_systems_lab\Process-Scheduling-Algos\objects\process\processes.cpp> // ! Figure out how to use header file.

int main() {
    int timeQuantum;
    std::cout << "Enter the time quantum: ";
    std::cin >> timeQuantum;

    int numOfProcesses;
    std::cout << "Enter the number of processes: ";
    std::cin >> numOfProcesses;

    std::unordered_map<Process *, int> remainingBT;
    std::unordered_map<Process *, bool> isInQueue;
    for (int i = 0; i < numOfProcesses; i++) {
        int aT;
        std::cout << "Enter arrival time of process #" << i + 1 << ": ";
        std::cin >> aT;

        int bT;
        std::cout << "Enter burst time of process #" << i + 1 << ": ";
        std::cin >> bT;

        Process *temp = new Process(i + 1, aT, bT);
        remainingBT[temp] = bT;
        isInQueue[temp] = false;
        processes.push_back(temp);
    }

    int totalTime = 0;

    std::queue<Process *> readyQueue;
    readyQueue.push(processes[0]);
    int index = 0;
    while (!readyQueue.empty()) {
        Process *p = readyQueue.front();
        readyQueue.pop();

        if (remainingBT[p] > timeQuantum) {
            remainingBT[p] -= timeQuantum;
            totalTime += timeQuantum;

            for (int i = 0; i < processes.size(); i++) {
                if (
                    processes[i] -> getArrivalTime() <= totalTime &&
                    processes[i] -> getArrivalTime() > p -> getArrivalTime() &&
                    !isInQueue[processes[i]]
                ) {
                    readyQueue.push(processes[i]);
                    isInQueue[processes[i]] = true;
                }
            }

            readyQueue.push(p);
        } else {
            totalTime += remainingBT[p];
            remainingBT[p] = 0;

            p -> setCompletionTime(totalTime);
            p -> calculateTAT();
            p -> calculateWT();

            for (int i = 0; i < processes.size(); i++) {
                if (
                    processes[i] -> getArrivalTime() <= totalTime &&
                    processes[i] -> getArrivalTime() > p -> getArrivalTime() &&
                    !isInQueue[processes[i]]
                ) {
                    readyQueue.push(processes[i]);
                }
            }
        }
    }

    printTable();

    float avgWT = 0;
    float avgTAT = 0;
    for (auto i: processes) {
        avgWT += (float) i -> getWaitTime() / processes.size();
        avgTAT += (float) i -> getTurnAroundTime() / processes.size();
    }

    std::cout << "Average wait time: " << avgWT << std::endl
              << "Average turnaround time: " << avgTAT << std::endl;
}