// sample_backend.h

#ifndef SAMPLE_BACKEND_H
#define SAMPLE_BACKEND_H

#include "process.hpp"


void process_input(std::vector<process> &processes);

void fill_readyqueue_non_preemtive_fcfs(std::vector<process> processes, std::queue<int> &readyqueue);

void fill_readyqueue_non_preemtive_sjf(std::vector<process> &processes, std::queue<int> &readyqueue);

void initialize_processes_for_preemtive(std::vector<process> &processes);

void execute_preemptive_sjf(std::vector<process> &processes);

void execute_round_robin(std::vector<process> &processes, std::queue<int> &readyqueue);

void execute_priority_non_preemptive(std::vector<process> &processes);

void execute_priority_preemptive(std::vector<process> &processes);

void calculate_TT_WT_RT(std::vector<process> &processes);

void executing_readyqueue_fcfs(std::vector<process> &processes, std::queue<int> readyqueue);

#endif
