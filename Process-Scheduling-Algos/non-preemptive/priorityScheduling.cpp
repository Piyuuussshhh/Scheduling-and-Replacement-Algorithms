#include <iostream>
#include <vector>
#include <algorithm>

#include <C:\Users\Piyush\Desktop\Programming\C++\College\sem4\operating_systems_lab\Process-Scheduling-Algos\objects\process\processes.cpp> // ! Figure out how to use header file.

int main() {
    int numOfProcesses;
    std::cout << "Enter the number of processes: ";
    std::cin >> numOfProcesses;

    std::vector<bool> isCompleted;
    for (int i = 0; i < numOfProcesses; i++) {
        int aT;
        std::cout << "Enter arrival time of process #" << i + 1 << ": ";
        std::cin >> aT;

        int bT;
        std::cout << "Enter burst time of process #" << i + 1 << ": ";
        std::cin >> bT;

        int priority;
        std::cout << "Enter priority of process #" << i + 1 << " (lower the number, higher the priority): ";
        std::cin >> priority;

        Process *temp = new Process(i + 1, aT, bT, priority);
        isCompleted.push_back(false);
        processes.push_back(temp);
    }

    sort(processes.begin(), processes.end(), [](Process *p1, Process *p2) {
        if (p1 -> getArrivalTime() == p2 -> getArrivalTime()) {
            return p1 -> getPriority() < p2 -> getPriority();
        }
        return p1 -> getArrivalTime() < p2 -> getArrivalTime();
    });

    int totalTime = 0;
    for (int i = 0; i < processes.size(); i++) {
        int index = -1;
        int maxPriority = INT_MAX;

        for (int j = 0; j < processes.size(); j++) {
            if (
                processes[j] -> getArrivalTime() <= totalTime &&
                !isCompleted[j]
            ) {
                if (processes[j] -> getPriority() < maxPriority) {
                    index = j;
                    maxPriority = processes[j] -> getPriority();
                } else if (processes[j] -> getPriority() == maxPriority) {
                    if (processes[j] -> getArrivalTime() < processes[index] -> getArrivalTime()) {
                        index = j;
                        maxPriority = processes[i] -> getPriority();
                    }
                }
            }
        }

        Process *p = processes[index];

        // Executing ith process
        totalTime += p -> getBurstTime();
        // Setting completion time of ith process.
        p -> setCompletionTime(totalTime);

        p -> calculateTAT();
        p -> calculateWT();

        isCompleted[index] = true;
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