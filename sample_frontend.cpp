// sample_frontend.cpp

#include <iostream>
#include <vector>
#include <queue>

#include "sample_frontend.hpp"
#include "sample_backend.hpp"
#include "sample_display_terminal.hpp"

void reset_processes(std::vector<process> &processes)
{
    for (process &p : processes) {

        p.WT = 0;
        p.TT = 0;
        p.RT = 0;
        p.CT = 0;

        p.assignTime = 0;

        p.lBT = p.BT;

        p.in_queue = false;
    }
}

void manual_process_input(
    std::vector<process> &processes)
{
    int n;

    std::cout << "\nEnter Number of Processes: ";
    std::cin >> n;

    for (int i = 0; i < n; i++) {

        process p;

        std::cout << "\nProcess P-" << i << '\n';

        p.pID = i;

        std::cout << "Arrival Time: ";
        std::cin >> p.AT;

        std::cout << "Burst Time: ";
        std::cin >> p.BT;

        std::cout << "Priority: ";
        std::cin >> p.P;

        processes.push_back(p);
    }
}

void algorithm_menu(
    std::vector<process> &processes)
{
    int choice;

    std::cout << "\n==============================\n";
    std::cout << "CPU Scheduling Algorithms\n";
    std::cout << "==============================\n";

    std::cout << "1. FCFS\n";
    std::cout << "2. Non-Preemptive SJF\n";
    std::cout << "3. Preemptive SJF (SRTF)\n";
    std::cout << "4. Round Robin\n";
    std::cout << "5. Non-Preemptive Priority\n";
    std::cout << "6. Preemptive Priority\n";

    std::cout << "\nEnter Choice: ";
    std::cin >> choice;

    std::queue<int> readyqueue;

    reset_processes(processes);

    switch (choice) {

        case 1:

            fill_readyqueue_non_preemtive_fcfs(
                processes,
                readyqueue
            );

            executing_readyqueue_fcfs(
                processes,
                readyqueue
            );

            break;

        case 2:

            fill_readyqueue_non_preemtive_sjf(
                processes,
                readyqueue
            );

            executing_readyqueue_fcfs(
                processes,
                readyqueue
            );

            break;

        case 3:

            initialize_processes_for_preemtive(
                processes
            );

            execute_preemptive_sjf(
                processes
            );

            break;

        case 4:

            initialize_processes_for_preemtive(
                processes
            );

            std::cout << "\nEnter Time Quantum: ";
            std::cin >> timeQuantum;

            execute_round_robin(
                processes
            );

            break;

        case 5:

            execute_priority_non_preemptive(
                processes
            );

            break;

        case 6:

            initialize_processes_for_preemtive(
                processes
            );

            execute_priority_preemptive(
                processes
            );

            break;

        default:

            std::cout << "\nInvalid Choice\n";
            return;
    }

    calculate_TT_WT_RT(processes);

    display_final_result(
        processes,
        readyqueue
    );
}

void launch_frontend()
{
    std::vector<process> processes;

    std::cout << "=====================================\n";
    std::cout << "CPU Scheduling Simulator\n";
    std::cout << "=====================================\n";

    manual_process_input(processes);

    display_table_on_terminal(processes);

    algorithm_menu(processes);
}