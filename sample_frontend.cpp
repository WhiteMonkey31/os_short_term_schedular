#include "sample_frontend.hpp"
#include "sample_backend.hpp"
#include "sample_display_terminal.hpp"

#include "include/SFML/Graphics.hpp"
#include <iostream>
#include <sstream>



void drawText( sf::RenderWindow& window, sf::Font& font, const std::string& str, int size, float x, float y) {
    sf::Text t(font, str, size);

    t.setPosition({x, y});

    window.draw(t);
}

void launch_frontend(){

    sf::RenderWindow window(sf::VideoMode({1200, 700}), "OS Scheduler Simulator");

    sf::Font font;

    if (!font.openFromFile("assets/sample_arial.ttf")) {

        std::cout << "Font not found\n";
        return;
    }

    std::vector<process> processes;

    int selectedAlgorithm = 0;

    bool simulationDone = false;

    // Sample Input
    // processes.push_back({0,3,3,2});
    // processes.push_back({1,4,1,5});
    // processes.push_back({2,2,2,3});
    // processes.push_back({3,0,4,1});
    // processes.push_back({4,1,5,4});

    process_input(processes);       // to input the processes 

    while (window.isOpen()) {

    while (const std::optional event = window.pollEvent())
    {
        // Close Window
        if (event->is<sf::Event::Closed>()) {

            window.close();
        }

        // Keyboard Input
        if (const auto* keyPressed =
            event->getIf<sf::Event::KeyPressed>())
        {
            // FCFS
            if (keyPressed->code == sf::Keyboard::Key::Num1)
            {
                selectedAlgorithm = 1;
            }

            // Non Preemptive SJF
            else if (keyPressed->code == sf::Keyboard::Key::Num2)
            {
                selectedAlgorithm = 2;
            }

            // Preemptive SJF
            else if (keyPressed->code == sf::Keyboard::Key::Num3)
            {
                selectedAlgorithm = 3;
            }

            // Round Robin
            else if (keyPressed->code == sf::Keyboard::Key::Num4)
            {
                selectedAlgorithm = 4;
            }

            // Priority Non Preemptive
            else if (keyPressed->code == sf::Keyboard::Key::Num5)
            {
                selectedAlgorithm = 5;
            }

            // Priority Preemptive
            else if (keyPressed->code == sf::Keyboard::Key::Num6)
            {
                selectedAlgorithm = 6;
            }

            // ENTER
            else if (keyPressed->code == sf::Keyboard::Key::Enter)
            {
                initialize_processes_for_preemtive(processes);

                if (selectedAlgorithm == 1) {

                    std::queue<int> rq;

                    fill_readyqueue_non_preemtive_fcfs(processes, rq);

                    executing_readyqueue_fcfs(processes, rq);
                }

                else if (selectedAlgorithm == 2) {

                    std::queue<int> rq;

                    fill_readyqueue_non_preemtive_sjf(processes, rq);

                    executing_readyqueue_fcfs(processes, rq);
                }

                else if (selectedAlgorithm == 3) {

                    execute_preemptive_sjf(processes);
                }

                else if (selectedAlgorithm == 4) {

                    std::queue<int> rq;

                    execute_round_robin(processes, rq);
                }

                else if (selectedAlgorithm == 5) {

                    execute_priority_non_preemptive(processes);
                }

                else if (selectedAlgorithm == 6) {

                    execute_priority_preemptive(processes);
                }

                calculate_TT_WT_RT(processes);

                simulationDone = true;
            }
        }
    }

    window.clear(sf::Color(30, 30, 30));

    drawText(window, font, "OS Scheduler Simulator", 36, 350, 20);

    drawText(window, font, "Choose Algorithm:", 24, 40, 100);

    drawText(window, font, "1 - FCFS", 22, 60, 150);

    drawText(window, font, "2 - Non Preemptive SJF", 22, 60, 190);

    drawText(window, font, "3 - Preemptive SJF", 22, 60, 230);

    drawText(window, font, "4 - Round Robin", 22, 60, 270);

    drawText(window, font, "5 - Priority Non Preemptive", 22, 60, 310);

    drawText(window, font, "6 - Priority Preemptive", 22, 60, 350 );

    drawText(window, font, "Press ENTER to Run", 24, 60, 430);

    std::string algoName = "None";

    if (selectedAlgorithm == 1)
        algoName = "FCFS";

    else if (selectedAlgorithm == 2)
        algoName = "Non Preemptive SJF";

    else if (selectedAlgorithm == 3)
        algoName = "Preemptive SJF";

    else if (selectedAlgorithm == 4)
        algoName = "Round Robin";

    else if (selectedAlgorithm == 5)
        algoName = "Priority Non Preemptive";

    else if (selectedAlgorithm == 6)
        algoName = "Priority Preemptive";

    drawText(window, font, "Selected: " + algoName, 24, 500, 120);

    // Display Result Table
    if (simulationDone) {

        drawText(window, font, "Results", 28, 500, 180);

        drawText(window, font, "PID   AT   BT   P   WT   TT   RT   CT", 20, 500, 230);

        int y = 270;

        for (const process &p : processes) {

            std::stringstream ss;

            ss
            << p.pID << "       "
            << p.AT << "       "
            << p.BT << "       "
            << p.P << "       "
            << p.WT << "       "
            << p.TT << "       "
            << p.RT << "       "
            << p.CT;

            drawText(window, font, ss.str(), 18, 500, y);

            y += 40;
        }
    }

    window.display();
}
}       



// for algorithm select on terminal
void algo_select_terminal(std::vector<process> &processes, std::queue<int> &readyqueue){
    
        process_input(processes);               // to input processes and their data

        display_table_on_terminal(processes);           // to display the initial values inputed

        
        // for preemtive processes (to initiallize lbt) 
        initialize_processes_for_preemtive(processes);      // to initialize lBT(left brust time variable) for preemtive sjf

        int num{};
        std::cout<<"Algorithms Available: \n";
        std::cout<<"1. FCFS.\n";
        std::cout<<"2. SJF (Non-Preemtive).\n";
        std::cout<<"3. SJF (Preemtive).\n";
        std::cout<<"4. Round Robin.\n";
        std::cout<<"5. Priority (Non-Preemtive).\n";
        std::cout<<"6. Priority (Preemtive).\n";
        std::cout<<"\nChoose Option (1-6): ";
        std::cin>>num;

        switch(num){
            case 1:{
                std::cout<<"Executing FCFS (First Come, First Serve):\n";
                
                // for fcfs
                fill_readyqueue_non_preemtive_fcfs(processes, readyqueue);       // to fill process into readyqueue in fcfs
                display_readyqueue(processes,readyqueue);                                                // to see the readyqueue data that is being stored in it.
                executing_readyqueue_fcfs(processes, readyqueue);                  // to calculate CT of each process

                break;
            }
            case 2:{
                std::cout<<"Executing SJF (Non-Preemtive):\n";
                
                // for non preemtive sjf
                fill_readyqueue_non_preemtive_sjf(processes,readyqueue);        // to fill readyqueue based on non preemtive SFJ
                display_readyqueue(processes,readyqueue);                                              // to see the readyqueue data that is being stored in it.
                executing_readyqueue_fcfs(processes, readyqueue);               // to calculate CT of each process
                break;
            }
            case 3:{
                std::cout<<"Executing SFJ (Preemtive).\n";
                
                // for preemtive sjf
                execute_preemptive_sjf(processes);                  // to execute processes in preemtive sjf (does not use readyqueue)

                break;
            }
            case 4:{
                std::cout<<"Executing Round Robin.\n";
                
                // for round robin
                execute_round_robin(processes, readyqueue);

                break;
            }
            case 5:{
                std::cout<<"Executing Priority (Non-Preemtive).\n";

                // for priority (non preemtive)
                execute_priority_non_preemptive(processes);         // for non preemtive priority 

                break;
            }
            case 6:{
                std::cout<<"Executing Priority (Preemtive).\n";

                // for priority (preemtive)
                execute_priority_preemptive(processes);             // for preemtive priority
            }
            default:{
                std::cout<<"Sorry, you have selected wrong option. Please select the correct option.\n";
                // recursion 
                // algo_select_terminal(processes,readyqueue);
            }
        }

        // for calculations
        calculate_TT_WT_RT(processes);                 // improved version to calculate the remaining data from CT

        // to display final result
        display_final_result(processes, readyqueue);                // to display the final results and calculations table (Gant Chart)
    
}
