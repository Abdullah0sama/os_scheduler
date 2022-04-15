#if !defined(__SCHEDULE_LIST__)
#define __SCHEDULE_LIST__

#include <vector>
#include <map>
#include "./TimeFrame.h"

class PMetric
{  
public:
    int waitingTime;
    int turnAroundTime;
    PMetric() {

    }
    PMetric(int waitingT, int turnAroundT) {
        waitingTime = waitingT;
        turnAroundTime = turnAroundT;
    }
};
class ScheduleList
{
private:
    std::vector<TimeFrame> timeline;
    std::map<Process::ProcessPtr, PMetric> processMetrics;
public:
    std::vector<TimeFrame> getTimeline() const;
    std::vector<Process::ProcessPtr> getProcesses() const;
    PMetric getProcessMetric(const Process::ProcessPtr& process) const;
    int numberOfProcesses() const;
    void addTimeFrame(const TimeFrame& timeFrame);

};



#endif // __SCHEDULE_LIST__
