#ifndef TIMER_H
#define TIMER_H


class Timer {
 public:
	
	Timer();
	~Timer();

	void start();
	void pause();

	void reset();

	Uint32 getTimer();

 private:
	Uint32 mTimer, mLastTime;
};

#endif
