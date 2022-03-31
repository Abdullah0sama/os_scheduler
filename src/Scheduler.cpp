#include "./Scheduler.h"


void Scheduler::addProcess(const Process& process) {
    processContainer.push_back(process);
}

uint Scheduler::processCount() {
    return processContainer.size();
}

