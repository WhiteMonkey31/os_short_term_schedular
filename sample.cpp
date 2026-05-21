

#include "sample_frontend.hpp"

#include "sample_backend.hpp"
#include "sample_display_terminal.hpp"




int main(){

    bool terminal{true};       // keep false for Graphic, True for Terminal based application run
    // bool terminal{false};

    if(!terminal){
        launch_frontend();
    }
    else if(terminal){

        std::vector<process> processes;
        std::queue<int> readyqueue;

        algo_select_terminal(processes, readyqueue);

    }

    return 0;
}


