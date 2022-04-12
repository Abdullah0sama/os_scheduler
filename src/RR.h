#if !defined(RR_SCH)
#define RR_SCH

#include "Scheduler.h"
#include <algorithm>
#include <queue>
class RR: public Scheduler
{
private:
    /* data */
public:
    ScheduleList schedule();
};


ScheduleList RR::schedule() {
    ScheduleList schList;
    if(processContainer.empty()) 
        return schList;

    std::sort(processContainer.begin(), processContainer.end(), arrivalTime_LessThan());
    std::queue<ActiveProcess> readyQueue;
    int curTime = 0;
    int arrivedProcess = 0;

    while(arrivedProcess < processContainer.size() || !readyQueue.empty()) {
        // Adding Idle TimeFrame
        if(readyQueue.empty() && arrivedProcess < processContainer.size() && processContainer[arrivedProcess] -> getArrivalTime() > curTime) {
            schList.addTimeFrame(TimeFrame(curTime, processContainer[arrivedProcess] -> getArrivalTime()));
            curTime = processContainer[arrivedProcess] -> getArrivalTime();
        }
        // Adding arrived processes to waitingProcesses
        while(arrivedProcess < processContainer.size() && processContainer[arrivedProcess] -> getArrivalTime() <= curTime) {
            readyQueue.push(ActiveProcess(processContainer[arrivedProcess]));
            arrivedProcess++;
        }
        
        ActiveProcess curProcess = readyQueue.front();
        readyQueue.pop();
        int usedBurstTime = -1;
        if(curProcess.leftBurstTime <= getQuantum()) {
            usedBurstTime = curProcess.leftBurstTime;
        } else {
            usedBurstTime = getQuantum();
            curProcess.leftBurstTime -= usedBurstTime;
            readyQueue.push(curProcess);
        }
        schList.addTimeFrame(TimeFrame(curTime, curTime + usedBurstTime, curProcess.process));
        curTime += usedBurstTime;

    }
    return schList;
}

#endif // RR_SCH
