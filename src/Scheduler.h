#if !defined(_SCHEDULER)
#define _SCHEDULER

#include "./Process.h"
#include <vector>
// #include "ScheduleList.h"

class Scheduler
{
protected:
    std::vector<Process> processContainer;
public:
    virtual void schedule() = 0;
    void addProcess(const Process& process);
    unsigned int processCount();
};


#endif // _SCHEDULER
