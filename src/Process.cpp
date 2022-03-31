#include "Process.h"


Process::Process(std::string name, uint arrivalTime, uint burstTime, uint priority) {   
    this -> name = name;
    this -> arrivalTime = arrivalTime;
    this -> burstTime = burstTime;
    this -> priority = priority;
}

uint Process::getBurstTime() {
    return burstTime;
}

uint Process::getArrivalTime() {
    return arrivalTime;
}

uint Process::getPriority() {
    return priority;
}

std::string Process::getName() {
    return name; 
}