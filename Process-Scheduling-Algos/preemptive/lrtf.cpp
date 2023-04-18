#include <iostream>
#include <vector>
#include <algorithm>

#include <C:\Users\Piyush\Desktop\Programming\C++\College\sem4\operating_systems_lab\Process-Scheduling-Algos\objects\process\processes.cpp> // ! Figure out how to use header file.

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

        Process *temp = new Process(i + 1, aT, bT);
        remainingBT.push_back(bT);
        isCompleted.push_back(false);
        processes.push_back(temp);
    }

    int totalTime = 0;
    int completedProcesses = 0;
    int maxIndex;

    while (completedProcesses != numOfProcesses) {
        maxIndex = -1;
        int maxBurstTime = INT_MIN;

        // This for loop finds the process with the minimum burst time that has arrived till now.
        for (int i = 0; i < numOfProcesses; i++) {
            if (
                processes[i] -> getArrivalTime() <= totalTime &&
                remainingBT[i] > maxBurstTime &&
                !isCompleted[i]
            ) {
                maxIndex = i;
                maxBurstTime = remainingBT[i];
            }
        }

        if (maxIndex == -1) {
            totalTime++;
        } else {
            remainingBT[maxIndex]--;
            totalTime++;

            if (remainingBT[maxIndex] == 0) {
                completedProcesses++;
                processes[maxIndex] -> setCompletionTime(totalTime);

                processes[maxIndex] -> calculateTAT();
                processes[maxIndex] -> calculateWT();

                isCompleted[maxIndex] = true;
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