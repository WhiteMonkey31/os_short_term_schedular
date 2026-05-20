// #include<iostream>
// // #include<string>
// #include<vector>
// #include<queue>
// #include<algorithm>

#include "sample_backend.hpp"
#include "sample_display_terminal.hpp"

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



}



// void display_logs_on_terminal(const std::vector<process> processes){

// }



int main(){
    

    std::vector<process> processes;
    std::queue<int> readyqueue;


    process_input(processes);               // to input processes and their data

    display_table_on_terminal(processes);           // to display the initial values inputed


    // for fcfs
    // fill_readyqueue_non_preemtive_fcfs(processes, readyqueue);       // to fill process into readyqueue in fcfs


    // for non preemtive sjf
    // fill_readyqueue_non_preemtive_sjf(processes,readyqueue);        // to fill readyqueue based on non preemtive SFJ



    // display_readyqueue(processes,readyqueue);               // to see the readyqueue data that is being stored in it.



    // display_logs_on_terminal(processes);

    
    // for fcfs
    // executing_readyqueue_fcfs(processes, readyqueue);           // to calculate CT of each process


    // for preemtive processes (to initiallize lbt) 
    initialize_processes_for_preemtive(processes);      // to initialize lBT(left brust time variable) for preemtive sjf
    

    // for preemtive sjf
    // execute_preemptive_sjf(processes);                  // to execute processes in preemtive sjf (does not use readyqueue)


    // for round robin
    // execute_round_robin(processes);


    // for priority
    // execute_priority_non_preemptive(processes);         // for non preemtive priority 
    execute_priority_preemptive(processes);             // for preemtive priority




    // for calculations
    calculate_TT_WT_RT(processes);                 // improved version to calculate the remaining data from CT

    // to display final result
    display_final_result(processes, readyqueue);                // to display the final results and calculations table (Gant Chart)
    


    return 0;
}