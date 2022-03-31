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
    std::string getName();
    uint getArrivalTime();
    uint getBurstTime();
    uint getPriority();
};


#endif // _PROCESS
