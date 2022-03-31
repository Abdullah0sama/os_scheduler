#if !defined(_PROCESS)
#define _PROCESS

#include<string>

class Process
{
private:
    std::string name;
    uint arrivalTime;
    uint burstTime;
    uint priority;
public:
    Process(std::string name, uint arrivalTime = 0, uint burstTime = 0, uint priority = 0);
    std::string getName() const;
    uint getArrivalTime() const;
    uint getBurstTime() const;
    uint getPriority() const;
};


struct arrivalTime_LessThan {
    bool operator () (const Process& p1, const Process& p2) const {
        return p1.getArrivalTime() < p2.getArrivalTime();
    }
};


#endif // _PROCESS
