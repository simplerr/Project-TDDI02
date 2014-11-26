#include "Timer.h"

Timer::Timer()
{
    mPaused = true;
    mPauseSum = 0;
}

Timer::~Timer()
{

}

void Timer::start()
{
    mPaused = false;
    mStartTime = std::chrono::high_resolution_clock::now();
}

void Timer::pause()
{
    auto now  = std::chrono::high_resolution_clock::now();
    auto sum = std::chrono::duration_cast<std::chrono::milliseconds>(now - mStartTime).count();
    mPauseSum += sum;
    mPaused = true;
}

void Timer::reset()
{
    // todo
    mStartTime = std::chrono::high_resolution_clock::now();
    mPauseSum = 0;
    mPaused = false;
}

int Timer::getMilliseconds()
{
    if(mPaused)
	return mPauseSum;
    else
    {
	auto now  = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(now - mStartTime).count() + mPauseSum;
    }
}

float Timer::getSeconds()
{
    int millis = getMilliseconds();
    float seconds = millis / 1000.0;
    seconds = int(seconds * 100) / 100.0;
    return seconds;
}
