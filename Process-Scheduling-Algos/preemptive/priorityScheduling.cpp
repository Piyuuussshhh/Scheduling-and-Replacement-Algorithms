#include <iostream>
#include <vector>

#include <C:\Users\Piyush\Desktop\Programming\C++\College\sem4\operating_systems_lab\Process-Scheduling-Algos\objects\process\processes.cpp>

int main() {
    int numOfProcesses;
    std::cout << "Enter the number of processes: ";
    std::cin >> numOfProcesses;

    // To store the remaining burst times of every process.
    std::vector<int> remainingBT;
    // A boolean vector to store if the process at an index is completed or not.
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
        remainingBT.push_back(bT);
        isCompleted.push_back(false);
        processes.push_back(temp);
    }

    int totalTime = 0;
    int completedProcesses = 0;
    int minIndex;

    while (completedProcesses != numOfProcesses) {
        minIndex = -1;
        int minBurstTime = INT_MAX;
        int maxPriority = INT_MAX;
        for (int i = 0; i < numOfProcesses; i++) {
            if (
                processes[i] -> getArrivalTime() <= totalTime &&
                !isCompleted[i]
            ) {
                if (processes[i] -> getPriority() < maxPriority) {
                    minIndex = i;
                    minBurstTime = remainingBT[i];
                    maxPriority = processes[i] -> getPriority();
                } else if (processes[i] -> getPriority() == maxPriority) {
                    if (processes[i] -> getArrivalTime() < processes[minIndex] -> getArrivalTime()) {
                        minIndex = i;
                        minBurstTime = remainingBT[i];
                        maxPriority = processes[i] -> getPriority();
                    }
                }
            }
        }

        if (minIndex == -1) {
            totalTime++;
        } else {
            remainingBT[minIndex]--;
            totalTime++;

            if (remainingBT[minIndex] == 0) {
                completedProcesses++;
                processes[minIndex] -> setCompletionTime(totalTime);

                processes[minIndex] -> calculateTAT();
                processes[minIndex] -> calculateWT();

                isCompleted[minIndex] = true;
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