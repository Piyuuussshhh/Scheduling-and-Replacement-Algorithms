#include <iostream>
#include <vector>
#include <algorithm>

#include <C:\Users\Piyush\Desktop\Programming\C++\College\sem4\operating_systems_lab\Process-Scheduling-Algos\objects\process\processes.cpp> // ! Figure out how to use header file.

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
        return p1 -> getArrivalTime() < p2 -> getArrivalTime();
    });

    int totalTime = 0;
    for (int i = 0; i < processes.size(); i++) {
        Process *p = processes[i];

        // Executing ith process
        totalTime += p -> getBurstTime();
        // Setting completion time of ith process.
        p -> setCompletionTime(totalTime);

        p -> calculateTAT();
        p -> calculateWT();
    }

    printTable();
}