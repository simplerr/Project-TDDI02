#include "Timer.h"

Timer::Timer()
{
	mTimer = 0;
	mLastTime = 0;
}

void Timer::start()
{
	mTimer = SDL_GetTicks();
}

void Timer::pause()
{
	mLastTime = mTimer;
}

void Timer::reset()
{
	// todo
	mLastTime = 0;
}

Uint32 Timer::getTimer()
{
	return mLastTime;
}
