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
    int priority;
public:
    Process(int id, int aT, int bT);
    Process(int id, int aT, int bT, int priority);
    bool operator ==(Process *p2);

    int getId();
    int getArrivalTime();
    int getBurstTime();
    int getCompletionTime();
    int getTurnAroundTime();
    int getWaitTime();
    int getPriority();

    void setCompletionTime(int);
    void calculateTAT();
    void calculateWT();
};

#endif