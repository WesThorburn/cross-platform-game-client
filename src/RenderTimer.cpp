#include "RenderTimer.h"

const int RenderTimer::PRINT_FREQUENCY = 60;

RenderTimer::RenderTimer() : Timer(){}

void RenderTimer::start(){
	Timer::start();
}

void RenderTimer::stop(){
	Timer::stop();
}

void RenderTimer::print(){
	if(m_intervals.size() < PRINT_FREQUENCY){
		return;
	}
	Timer::print();
	Timer::reset();
}