#if !defined(_SCHEDULER)
#define _SCHEDULER

#include <vector>
#include "./Process.h"
#include "./ScheduleList.h"

class Scheduler
{
protected:
    std::vector<Process> processContainer;
public:
    virtual ScheduleList schedule() = 0;
    void addProcess(const Process& process);
    unsigned int processCount();
};


#endif // _SCHEDULER
