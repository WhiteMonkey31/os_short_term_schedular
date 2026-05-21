#include "sample_backend.hpp"
#include <algorithm>
#include <iostream>

int currentTime{0};
int total_cpu_time{0};
int timeQuantum{2};
int minPriority{0};
int maxPriority{5};



void process_input(std::vector<process> &processes){
    
    // proceesses must start with process 0 and then continue forward
    // processes.push_back({0,3,3,4});
    // processes.push_back({1,4,1});
    // processes.push_back({2,2,2});
    // processes.push_back({3,0,4});
    // processes.push_back({4,1,5});


    
    processes.push_back({0,3,3,2});
    processes.push_back({1,4,1,5});
    processes.push_back({2,2,2,3});
    processes.push_back({3,0,4,1});
    processes.push_back({4,1,5,4});

    
    // Sample Input
    // processes.push_back({0,3,3,2});
    // processes.push_back({1,4,1,5});
    // processes.push_back({2,2,2,3});
    // processes.push_back({3,0,4,1});
    // processes.push_back({4,1,5,4});

}


void fill_readyqueue_non_preemtive_fcfs(std::vector<process> processes, std::queue<int> &readyqueue){        // to put processes in Ready Queue in FCFS
    // int n=processes.size();
    // bool check[n];
    // for(int i{0};i<sizeof(check);i++){
    //     check[i]=false;
    // }
    for(int j{0};j<processes.size();j++){
        for(int i{0};i<processes.size();i++){
            if(processes[i].AT<=currentTime){
                
                if(!processes[i].in_queue){
                    readyqueue.push(processes[i].pID);
                    processes[i].in_queue=true;
                }
                
            }
        }
        currentTime++;
    }
    
}

void fill_readyqueue_non_preemtive_sjf(std::vector<process> &processes, std::queue<int> &readyqueue){   // to fill readyqueue for non-preemtive sjf

    int completed = 0;
    int currentTime = 0;

    while (completed < processes.size()) {

        // store AVAILABLE process indices
        std::vector<int> available_processes;

        // find all arrived and unfinished processes
        for (int i = 0; i < processes.size(); i++) {

            if (processes[i].AT <= currentTime &&
                !processes[i].in_queue)
            {
                available_processes.push_back(i);
            }
        }

        // if CPU is idle
        if (available_processes.empty()) {

            currentTime++;
            continue;
        }

        // find shortest burst time process
        auto shortest = std::min_element(

            available_processes.begin(),
            available_processes.end(),

            [&](int a, int b) {

                return processes[a].BT <
                       processes[b].BT;
            }
        );

        int idx = *shortest;

        // push INDEX into queue
        readyqueue.push(idx);

        processes[idx].in_queue = true;

        // simulate execution
        currentTime += processes[idx].BT;

        completed++;
    }
}

void initialize_processes_for_preemtive(std::vector<process> &processes)
{
    for (process &p : processes) {

        p.lBT = p.BT;
    }
}

void execute_preemptive_sjf(std::vector<process> &processes)
{
    int completed = 0;
    int currentTime = 0;

    while (completed < processes.size()) {

        int shortest = -1;

        // Find shortest remaining job
        for (int i = 0; i < processes.size(); i++) {

            if (processes[i].AT <= currentTime &&
                processes[i].lBT > 0)
            {
                if (shortest == -1 ||
                    processes[i].lBT <
                    processes[shortest].lBT)
                {
                    shortest = i;
                }
            }
        }

        // CPU idle
        if (shortest == -1) {

            currentTime++;
            continue;
        }

        // First response time
        if (processes[shortest].lBT ==
            processes[shortest].BT)
        {
            processes[shortest].assignTime =
                currentTime;
        }

        // Execute for 1 unit
        processes[shortest].lBT--;

        currentTime++;

        // Process finished
        if (processes[shortest].lBT == 0) {

            processes[shortest].CT =
                currentTime;

            completed++;
        }
    }
}

void execute_round_robin(std::vector<process> &processes, std::queue<int> &readyqueue){      // to execute process in round robin 

    // std::queue<int> readyqueue;

    int currentTime = 0;
    int completed = 0;

    while (completed < processes.size()) {

        // Add newly arrived processes
        for (int i = 0; i < processes.size(); i++) {

            if (processes[i].AT <= currentTime &&
                !processes[i].in_queue &&
                processes[i].lBT > 0)
            {
                readyqueue.push(i);

                processes[i].in_queue = true;
            }
        }

        // CPU Idle
        if (readyqueue.empty()) {

            currentTime++;
            continue;
        }

        int idx = readyqueue.front();
        readyqueue.pop();

        // First response
        if (processes[idx].lBT ==
            processes[idx].BT)
        {
            processes[idx].assignTime =
                currentTime;
        }

        // Execute process
        int executeTime =
            std::min(timeQuantum,
                     processes[idx].lBT);

        processes[idx].lBT -= executeTime;

        currentTime += executeTime;

        // Add newly arrived during execution
        for (int i = 0; i < processes.size(); i++) {

            if (processes[i].AT <= currentTime &&
                !processes[i].in_queue &&
                processes[i].lBT > 0)
            {
                readyqueue.push(i);

                processes[i].in_queue = true;
            }
        }

        // If process finished
        if (processes[idx].lBT == 0) {

            processes[idx].CT =
                currentTime;

            completed++;
        }
        else {

            // Put back into queue
            readyqueue.push(idx);
        }
    }
}

void execute_priority_non_preemptive(std::vector<process> &processes){

    int completed = 0;
    int currentTime = 0;

    while (completed < processes.size()) {

        int highest = -1;

        // Find highest priority process
        for (int i = 0; i < processes.size(); i++) {

            if (processes[i].AT <= currentTime &&
                !processes[i].in_queue)
            {
                if (highest == -1 ||
                    processes[i].P >
                    processes[highest].P)
                {
                    highest = i;
                }
            }
        }

        // CPU Idle
        if (highest == -1) {

            currentTime++;
            continue;
        }

        // Response time start
        processes[highest].assignTime =
            currentTime;

        // Execute completely
        currentTime += processes[highest].BT;

        processes[highest].CT =
            currentTime;

        processes[highest].in_queue = true;

        completed++;
    }
}

void execute_priority_preemptive(std::vector<process> &processes){
    int completed = 0;
    int currentTime = 0;

    while (completed < processes.size()) {

        int highest = -1;

        // Find highest priority available process
        for (int i = 0; i < processes.size(); i++) {

            if (processes[i].AT <= currentTime &&
                processes[i].lBT > 0)
            {
                if (highest == -1 ||
                    processes[i].P >
                    processes[highest].P)
                {
                    highest = i;
                }
            }
        }

        // CPU Idle
        if (highest == -1) {

            currentTime++;
            continue;
        }

        // First response
        if (processes[highest].lBT ==
            processes[highest].BT)
        {
            processes[highest].assignTime =
                currentTime;
        }

        // Execute for 1 unit
        processes[highest].lBT--;

        currentTime++;

        // Finished
        if (processes[highest].lBT == 0) {

            processes[highest].CT =
                currentTime;

            completed++;
        }
    }
}

void calculate_TT_WT_RT(std::vector<process> &processes){  // improved func to calculate the remaining data of the process from CT
    for(process &p:processes){
        p.TT=p.CT-p.AT;
        p.WT=p.TT-p.BT;
        p.RT=p.assignTime-p.AT;
    }

}

void executing_readyqueue_fcfs(std::vector<process> &processes, std::queue<int> readyqueue){           // to calculate CT of process in FCFS
    
    
    while(!readyqueue.empty()){
        int idx=readyqueue.front();
        readyqueue.pop();

        if(total_cpu_time<processes[idx].AT){
            total_cpu_time=processes[idx].AT;
        }
        processes[idx].assignTime=total_cpu_time;
        total_cpu_time+=processes[idx].BT;
        processes[idx].CT=total_cpu_time;

    }
}