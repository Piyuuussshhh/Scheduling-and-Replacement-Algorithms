#ifndef PROCESSES_H
#define PROCESSES_H

class Process {
private:
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnAroundTime;
    int waitTime;
public:
    Process(int id, int aT, int bT);
    int getId();
    int getArrivalTime();
    int getBurstTime();
    int getCompletionTime();
    int getTurnAroundTime();
    int getWaitTime();

    void setCompletionTime(int);
    void calculateTAT();
    void calculateWT();
};

#endif