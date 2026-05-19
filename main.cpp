#include<iostream>
// #include<string>
#include<vector>
#include<queue>

int currentTime{0};
int total_cpu_time{0};

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
    int assignTime;
    int cP;             // current Priority
    int lBT;            // left Brust Time
    bool in_queue{false};   // check whether process is in queue or not
    // int cpuT;           // CPU time to measure total completion time
    // int T_CT;           // total completion time
};

void process_input(std::vector<process> &processes){
    
    // proceesses must start with process 0 and then continue forward
    processes.push_back({0,3,3});
    processes.push_back({1,4,1});
    processes.push_back({2,2,2});
    processes.push_back({3,0,4});
    processes.push_back({4,1,5});
}

void display_table_on_terminal(const std::vector<process> processes){
    std::cout<<"Data Stored:\n\n";
    std::cout<<"pID\t|\tAT\t|\tBT\t|\tP\n";
    std::cout<<"------------------------------------------------------\n";
    for(const process &p : processes){
        std::cout<<"P-"<<p.pID<<"\t|\t"
                <<p.AT<<"\t|\t"
                <<p.BT<<"\t|\t"
                <<'\n';
        
    }
    std::cout<<"------------------------------------------------------\n";
}



void display_logs_on_terminal(const std::vector<process> processes){

}

void calculations_readyqueue_non_preemtive(std::vector<process> processes, std::queue<int> &readyqueue){
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

void calculations_fcfs_nonpreemtive(std::vector<process> &processes, std::queue<int> readyqueue){
    while(!readyqueue.empty()){
        int idx=readyqueue.front();
        processes[idx].TT=processes[idx].CT-processes[idx].AT;
        processes[idx].WT=processes[idx].TT-processes[idx].BT;
        processes[idx].RT=processes[idx].assignTime-processes[idx].AT;

        readyqueue.pop();
    }

}

void executing_process_fcfs(std::vector<process> &processes, std::queue<int> readyqueue){
    
    
    while(!readyqueue.empty()){
        int idx=readyqueue.front();
        processes[idx].assignTime=total_cpu_time;
        total_cpu_time+=processes[idx].BT;
        processes[idx].CT=total_cpu_time;


        readyqueue.pop();
    }
}

void display_readyqueue(const std::vector<process> processes, std::queue<int> readyqueue){
    while(!readyqueue.empty()){
        int idx=readyqueue.front();
        readyqueue.pop();

        std::cout<<"Executing Process: "<<processes[idx].pID<<'\n';
    }
}

void display_final_result(const std::vector<process> processes, const std::queue<int> readyqueue){
    std::cout<<"pID\t|\tAT\t|\tBT\t|\tP\t|\tWT\t|\tTT\t|\tRT\t|\tCT\n";
    std::cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------\n";
    for(const process &p : processes){
        std::cout<<"P-"<<p.pID<<"\t|\t"
                <<p.AT<<"\t|\t"
                <<p.BT<<"\t|\t"
                <<p.P<<"\t|\t"
                <<p.WT<<"\t|\t"
                <<p.TT<<"\t|\t"
                <<p.RT<<"\t|\t"
                <<p.CT<<"\t|\t"
                <<'\n';
        
    }
    std::cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------\n";


}

int main(){
    std::cout<<"hello\n";

    std::vector<process> processes;
    std::queue<int> readyqueue;


    process_input(processes);

    display_table_on_terminal(processes);

    calculations_readyqueue_non_preemtive(processes, readyqueue);

    display_readyqueue(processes,readyqueue);

    // display_logs_on_terminal(processes);

    // executing_process_fcfs(processes, readyqueue);

    // calculations_fcfs_nonpreemtive(processes,readyqueue);

    

    display_final_result(processes, readyqueue);
    


    return 0;
}