#include<iostream>
// #include<string>
#include<vector>
#include<queue>

int currentTime{0};

struct process{
    // data fetch
    int pID;            // process ID
    int AT;             // Arrival Time
    int BT;             // Brust Time
    int P;              // Priority (initial)

    // calculations
    int WT;              // Waiting Time
    int TT;              // TurnAround Time
    int RT;             // Response time
    int CT;               // Completeion Time

    // to store dynamic data (automatic)
    int cP;             // current Priority
    int lBT;            // left Brust Time
    // int cpuT;           // CPU time to measure total completion time
    // int T_CT;           // total completion time
};

void display_table_on_terminal(const std::vector<process> &processes){
    std::cout<<"Data Stored:\n\n";
    std::cout<<"pID\t|\tAT\t|\tBT\t|\tP\n";
    std::cout<<"------------------------------------------------------\n";
    for(const process &p : processes){
        std::cout<<"P-"<<p.pID<<"\t|\t"
                <<p.AT<<"\t|\t"
                <<p.BT<<"\t|\t"
                <<'\n';
        
    }
}



void display_logs_on_terminal(const std::vector<process> &processes){

}

void calculations_non_preemtive(const std::vector<process> &processes, std::queue<int> &readyqueue){
    for(int i{0};i<processes.size();i++){
        if(processes[i].AT<=currentTime){
            readyqueue.push(processes[i].pID);
        }
    }
}

void display_readyqueue(const std::vector<process> &processes, std::queue<int> &readyqueue){
    while(!readyqueue.empty()){
        int idx=readyqueue.front();
        readyqueue.pop();

        std::cout<<"Executing Process: "<<processes[idx].pID<<'\n';
    }
}

int main(){
    std::cout<<"hello\n";

    std::vector<process> processes;
    std::queue<int> readyqueue;

    // proceesses must start with process 0 and then continue forward
    processes.push_back({0,3,3});
    processes.push_back({1,4,1});
    processes.push_back({2,2,2});
    processes.push_back({3,0,4});
    processes.push_back({4,1,5});

    display_table_on_terminal(processes);

    calculations_non_preemtive(processes, readyqueue);

    display_readyqueue(processes,readyqueue);

    // display_logs_on_terminal(processes);
    


    return 0;
}