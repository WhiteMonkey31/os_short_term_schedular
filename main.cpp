#include<iostream>
#include<string>
#include<vector>


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
};

void display_on_screen(const std::vector<process> &processes){
    std::cout<<"Data Stored:\n\n";
    std::cout<<"pID\t|\tAT\t|\tBT\t|\tP\n";
    std::cout<<"------------------------------------------------------\n";
    for(const process &p : processes){
        std::cout<<"P-"<<p.pID<<"\t|\t"
                <<p.AT<<"\t|\t"
                <<p.BT<<"\t|\t"
                <<p.P<<'\n';
        
    }
}

int main(){
    std::cout<<"hello\n";

    std::vector<process> processes;

    processes.push_back({1,0,5,2});
    processes.push_back({2,1,3,1});
    processes.push_back({3,2,8,4});


    display_on_screen(processes);

    


    return 0;
}