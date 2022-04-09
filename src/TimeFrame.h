#if !defined(__TIMEFRAME__)
#define __TIMEFRAME__

#include <memory>
#include "Process.h"

class TimeFrame
{
private:
    /* data */
public:
    const unsigned int start;
    const unsigned int end;
    std::shared_ptr<const Process> process;
    TimeFrame(unsigned int start, unsigned int end, const Process::ProcessPtr& process=nullptr): start(start), end(end),  process(process){

    };
    bool isIdle() {
        return process == nullptr;
    }
    std::string getName() {
        if(isIdle()) return "Idle";
        else return process -> getName();
    }
};



#endif // __TIMEFRAME__
