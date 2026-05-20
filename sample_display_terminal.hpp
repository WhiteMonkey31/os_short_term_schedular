#ifndef SAMPLE_DISPLAY_TERMINAL_H
#define SAMPLE_DISPLAY_TERMINAL_H

#include "process.hpp"

void display_table_on_terminal(const std::vector<process> processes);

void display_readyqueue(const std::vector<process> processes, std::queue<int> readyqueue);

void display_final_result(const std::vector<process> processes, const std::queue<int> readyqueue);

#endif