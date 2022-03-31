#include "./Scheduler.h"


void Scheduler::addProcess(const Process& process) {
    std::shared_ptr<const Process> copiedProcess(new Process(process));
    processContainer.push_back(copiedProcess);
}

uint Scheduler::processCount() {
    return processContainer.size();
}



