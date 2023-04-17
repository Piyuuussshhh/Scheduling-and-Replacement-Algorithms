#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#include <C:\Users\Piyush\Desktop\Programming\C++\College\sem4\operating_systems_lab\Process-Scheduling-Algos\objects\process\processes.cpp> // ! Figure out how to use header file.

bool isInProcessVector(Process *p, std::vector<Process *> arrivedProcesses) {
    for (auto i: arrivedProcesses) {
        if (i == p) {
            return true;
        }
    }
    return false;
}

int main() {
    int numOfProcesses;
    std::cout << "Enter the number of processes: ";
    std::cin >> numOfProcesses;

    for (int i = 0; i < numOfProcesses; i++) {
        int aT;
        std::cout << "Enter arrival time of process #" << i + 1 << ": ";
        std::cin >> aT;

        int bT;
        std::cout << "Enter burst time of process #" << i + 1 << ": ";
        std::cin >> bT;

        Process *temp = new Process(i + 1, aT, bT);
        processes.push_back(temp);
    }

    sort(processes.begin(), processes.end(), [](Process *p1, Process *p2) {
        if (p1 -> getArrivalTime() == p2 -> getArrivalTime()) {
            return p1 -> getBurstTime() < p2 -> getBurstTime();
        }
        return p1 -> getArrivalTime() < p2 -> getArrivalTime();
    });

    int totalTime = 0;
    std::queue<Process *> q;
    q.push(processes[0]);
    std::vector<Process *> arrivedProcesses;
    std::vector<Process *> executedProcesses;
    while (!q.empty()) {
        Process *p = q.front();
        q.pop();

        totalTime += p -> getBurstTime();
        p -> setCompletionTime(totalTime);

        p -> calculateTAT();
        p -> calculateWT();

        executedProcesses.push_back(p);

        std::cout << "While process #" << p -> getId() << " was executing:" << std::endl;
        for (auto i: processes) {
            if (
                (i -> getArrivalTime() > p -> getArrivalTime() && i -> getArrivalTime() < totalTime) &&
                !isInProcessVector(i, arrivedProcesses) &&
                !isInProcessVector(i, executedProcesses)
            ) {
                std::cout << "Process #" << i -> getId() << " arrived!" << std::endl;
                arrivedProcesses.push_back(i);
            }
        }

        if (!arrivedProcesses.empty()) {
            sort(arrivedProcesses.begin(), arrivedProcesses.end(), [](Process *p1, Process *p2) {
                if (p1 -> getBurstTime() == p2 -> getBurstTime()) {
                    return p1 -> getArrivalTime() < p2 -> getArrivalTime();
                } else if (
                    (p1 -> getBurstTime() == p2 -> getBurstTime()) &&
                    (p1 -> getArrivalTime() == p2 -> getArrivalTime())
                ) {
                    return p1 -> getId() < p2 -> getId();
                }
                return p1 -> getBurstTime() < p2 -> getBurstTime();
            });

            q.push(arrivedProcesses[0]);
            arrivedProcesses.erase(arrivedProcesses.begin());
        }
    }

    printTable(executedProcesses);

    float avgWT = 0;
    float avgTAT = 0;
    for (auto i: processes) {
        avgWT += (float) i -> getWaitTime() / processes.size();
        avgTAT += (float) i -> getTurnAroundTime() / processes.size();
    }

    std::cout << "Average wait time: " << avgWT << std::endl
              << "Average turnaround time: " << avgTAT << std::endl;
}