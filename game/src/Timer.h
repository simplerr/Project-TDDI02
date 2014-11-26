#ifndef TIMER_H
#define TIMER_H
#include <chrono>

class Timer {
 public:
	
    Timer();
    ~Timer();
    
    void start();
    void pause();
    
    void reset();
    
    int getMilliseconds();
    float getSeconds();

 private:
    std::chrono::high_resolution_clock::time_point mStartTime;
    bool mPaused;
    int mPauseSum;
};

#endif
