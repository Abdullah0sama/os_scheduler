#if !defined(_SCHEDULER)
#define _SCHEDULER

#include <vector>
#include "./Process.h"
#include "./ScheduleList.h"

class Scheduler
{
protected:
    std::vector<std::shared_ptr<const Process>> processContainer;
public:
    virtual ScheduleList schedule() = 0;
    void addProcess(const Process& process);
    unsigned int processCount();
};

struct arrivalTime_LessThan {
    bool operator () (std::shared_ptr<const Process>& p1, std::shared_ptr<const Process>& p2) const {
        return (p1 -> getArrivalTime() == p2 -> getArrivalTime()) ? p1 -> getBurstTime() < p2 -> getBurstTime() : p1 -> getArrivalTime() < p2 -> getArrivalTime();
    }
};

#endif // _SCHEDULER
