#include<iostream>
// #include<string>
#include<vector>
#include<queue>
#include<algorithm>

int currentTime{0};
int total_cpu_time{0};


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

void fill_readyqueue_non_preemtive_sjf(std::vector<process> &processes, std::queue<int> &readyqueue){         // to fill readyqueue based on non preemtive SJF
    // int shortJobID{};
    // bool isshort{false};
    
    for(int j{0};j<processes.size();j++){

        std::vector<int> available_processes;
        
        for(int i{0};i<processes.size();i++){

            int n=processes.size();
            // bool isShort[n];
            bool isShort{false};
            // for(bool x: isShort){
            //     x=false;
            // }

            bool isAvailable{false};
            if(!available_processes.empty()){
                auto it=std::find(available_processes.begin(), available_processes.end(), processes[i].pID);
                if(it!= available_processes.end()){
                    isAvailable=true;
                }else{
                    isAvailable=false;
                }
            }

            if(processes[i].AT<=currentTime){
                if(!isAvailable){
                    available_processes.push_back(processes[i].pID);
                    // available_processes.push_back(i);
                }
                for(int x: available_processes){
                    if(!processes[x].in_queue){
                        auto it=std::min_element(available_processes.begin(), available_processes.end(),
                        [&](int a, int b){
                            return processes[a].BT<processes[b].BT;
                        }
                    );
                    int shortestIdx=*it;
                    if(shortestIdx==i){
                        isShort=true;
                    }
                    // isShort=*it;
                        // if(*it==processes[i].pID){
                        //     isShort=true;
                        // }
                    }
                }
                

                if(!processes[i].in_queue && isShort){
                    readyqueue.push(processes[i].pID);
                    processes[i].in_queue=true;
                }
                
            }
        }
        currentTime++;
    }
}

// void calculations_fcfs_nonpreemtive(std::vector<process> &processes, std::queue<int> readyqueue){  // to calculate the remaining data from CT
//     while(!readyqueue.empty()){
//         int idx=readyqueue.front();
//         processes[idx].TT=processes[idx].CT-processes[idx].AT;
//         processes[idx].WT=processes[idx].TT-processes[idx].BT;
//         processes[idx].RT=processes[idx].assignTime-processes[idx].AT;

//         readyqueue.pop();
//     }

// }

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

void display_readyqueue(const std::vector<process> processes, std::queue<int> readyqueue){          // to display the data contained in Ready Queue
    while(!readyqueue.empty()){
        int idx=readyqueue.front();
        readyqueue.pop();

        std::cout<<"Executing Process: "<<processes[idx].pID<<'\n';
    }
}

void display_final_result(const std::vector<process> processes, const std::queue<int> readyqueue){          // to show the final output table
    std::cout<<"pID\t|\tAT\t|\tBT\t|\tP\t|\tWT\t|\tTT\t|\tRT\t|\tCT\n";
    std::cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------\n";
    for(const process p : processes){
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


    process_input(processes);               // to input processes and their data

    display_table_on_terminal(processes);           // to display the initial values inputed

    // fill_readyqueue_non_preemtive_fcfs(processes, readyqueue);       // to fill process into readyqueue in fcfs

    fill_readyqueue_non_preemtive_sjf(processes,readyqueue);        // to fill readyqueue based on non preemtive SFJ

    display_readyqueue(processes,readyqueue);               // to see the readyqueue data that is being stored in it.

    // display_logs_on_terminal(processes);

    

    executing_readyqueue_fcfs(processes, readyqueue);           // to calculate CT of each process

    // calculations_fcfs_nonpreemtive(processes,readyqueue);    // to calculate remaining data from CT, better to use the improved version  

    




    calculate_TT_WT_RT(processes);                 // improved version to calculate the remaining data from CT

    display_final_result(processes, readyqueue);                // to display the final results and calculations
    


    return 0;
}