#if !defined(_SCHEDULER)
#define _SCHEDULER

#include <vector>
#include "./Process.h"
#include "./ScheduleList.h"



class Scheduler
{
protected:
    std::vector<Process::ProcessPtr> processContainer;
public:
    virtual ScheduleList schedule() = 0;
    void addProcess(const Process& process);
    unsigned int processCount();
};

struct arrivalTime_LessThan {
    bool operator () (const Process::ProcessPtr& p1, const Process::ProcessPtr& p2) const {
        return p1 -> getArrivalTime() < p2 -> getArrivalTime();
    }
};

struct burstTime_cmp {
    bool operator () (const Process::ProcessPtr& p1, const Process::ProcessPtr& p2) const {
        if(p1 -> getArrivalTime() == p2 -> getArrivalTime()) return p1 -> getBurstTime() < p2 -> getBurstTime();
        else return p1 -> getBurstTime() < p2 -> getBurstTime();
    }
};


#endif // _SCHEDULER
