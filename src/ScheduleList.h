#if !defined(__SCHEDULE_LIST__)
#define __SCHEDULE_LIST__

#include <vector>
#include "./TimeFrame.h"

class ScheduleList
{
private:
public:
    std::vector<TimeFrame> timeline;
    inline void addTimeFrame(const TimeFrame& timeFrame);
};


void ScheduleList::addTimeFrame(const TimeFrame& timeFrame) {
    timeline.push_back(timeFrame);
}


#endif // __SCHEDULE_LIST__
