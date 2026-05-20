#ifndef PROCESS_H
#define PROCESS_H

#include <vector>
#include <queue>


extern int currentTime;
extern int total_cpu_time;
extern int timeQuantum;
extern int minPriority;
extern int maxPriority;

struct process{
    // data fetch
    int pID{0};            // process ID
    int AT{0};             // Arrival Time
    int BT{0};             // Brust Time
    int P{0};              // Priority (initial)

    // calculations
    int WT{0};              // Waiting Time
    int TT{0};              // TurnAround Time
    int RT{0};             // Response time
    int CT{0};               // Completeion Time

    // to store dynamic data (automatic)
    int assignTime{0};
    int cP{0};             // current Priority
    int lBT{0};            // left Brust Time
    bool in_queue{false};   // check whether process is in queue or not
    
    // int cpuT;           // CPU time to measure total completion time
    // int T_CT;           // total completion time
};

#endif