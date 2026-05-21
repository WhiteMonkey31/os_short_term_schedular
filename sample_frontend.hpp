// sample_frontend.h

#ifndef SAMPLE_FRONTEND_H
#define SAMPLE_FRONTEND_H

#include "process.hpp"

void launch_frontend();
void algo_select_terminal(std::vector<process> &processes, std::queue<int> &readyqueue);

#endif