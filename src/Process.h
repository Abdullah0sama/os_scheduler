#if !defined(_PROCESS)
#define _PROCESS

#include <string>
#include <memory>

class Process
{
private:
    std::string name;
    uint arrivalTime;
    uint burstTime;
    uint priority;
    uint leftBurstTime;
public:
    typedef std::shared_ptr<Process> ProcessPtr;
    Process(std::string name, uint arrivalTime = 0, uint burstTime = 0, uint priority = 0);
    std::string getName() const;
    uint getArrivalTime() const;
    uint getBurstTime() const;
    uint getPriority() const;
    uint getLeftBurstTime() const;
    void resetLeftBurstTime();
    void decrementLeftBurstTime(uint time);
};



#endif // _PROCESS
