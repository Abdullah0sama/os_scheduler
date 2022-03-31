#include "Process.h"


Process::Process(std::string name, uint arrivalTime, uint burstTime, uint priority) {   
    this -> name = name;
    this -> arrivalTime = arrivalTime;
    this -> burstTime = burstTime;
    this -> priority = priority;
}

uint Process::getBurstTime() const{
    return burstTime;
}

uint Process::getArrivalTime() const{
    return arrivalTime;
}

uint Process::getPriority() const{
    return priority;
}

std::string Process::getName() const{
    return name; 
}
