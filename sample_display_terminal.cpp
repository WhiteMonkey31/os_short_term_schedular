#include "sample_display_terminal.hpp"
#include <iostream>



void display_final_result(const std::vector<process> processes, const std::queue<int> readyqueue){          // to show the final output table
    std::cout<<"\n---------------------------------------------------------------------------------------------------------------------------------------------------\n";
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
    std::cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------\n\n";


}



void display_readyqueue(const std::vector<process> processes, std::queue<int> readyqueue){          // to display the data contained in Ready Queue
    while(!readyqueue.empty()){
        int idx=readyqueue.front();
        readyqueue.pop();

        std::cout<<"Executing Process: "<<processes[idx].pID<<'\n';
    }
}



void display_table_on_terminal(const std::vector<process> processes){
    bool priority_given{false};
    for(const process p:processes){
        if(p.P!=0){             // to check if priority is given or not?
            priority_given=true;
        }
    }
    std::cout<<"Data Given:\n";
    std::cout<<"------------------------------------------------------\n";
    std::cout<<"pID\t|\tAT\t|\tBT\t|\t";
    if(priority_given){
        std::cout<<"P";
    }
    std::cout<<"\n------------------------------------------------------\n";
    
    for(const process &p : processes){
        std::cout<<"P-"<<p.pID<<"\t|\t"
                <<p.AT<<"\t|\t"
                <<p.BT<<"\t|\t";
        if(priority_given){
            std::cout<<p.P<<"\t|\t";
        }
        std::cout<<'\n';
        
    }
    std::cout<<"------------------------------------------------------\n";
}
