#ifndef RENDER_TIMER_H
#define RENDER_TIMER_H

#include "Timer.h"

class RenderTimer: public Timer{
public:
	RenderTimer();
	void start();
	void stop();
	void print();
private:
	static const int PRINT_FREQUENCY;
};

#endif