#include "Process.h"


Process::Process(std::string name, uint arrivalTime, uint burstTime, uint priority) {   
    this -> name = name;
    this -> arrivalTime = arrivalTime;
    this -> burstTime = burstTime;
    this -> priority = priority;
    this -> leftBurstTime = this -> burstTime;
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

uint Process::getLeftBurstTime() const {
    return leftBurstTime;
}
void Process::resetLeftBurstTime() {
    leftBurstTime = burstTime;
}
void Process::decrementLeftBurstTime(uint time) {
    leftBurstTime -= time;
}

