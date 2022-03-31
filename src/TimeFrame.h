#if !defined(__TIMEFRAME__)
#define __TIMEFRAME__

class TimeFrame
{
private:
    /* data */
public:
    const unsigned int start;
    const unsigned int end;
    
    TimeFrame(unsigned int start, unsigned int end): start(start), end(end) {

    };
};



#endif // __TIMEFRAME__
