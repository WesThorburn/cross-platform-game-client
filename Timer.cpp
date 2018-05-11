#include <iostream>
#include <numeric>
#include <emscripten.h>
#include <emscripten/bind.h>
#include "Timer.h"

Timer::Timer(){}

void Timer::start(){
	m_startTimeMs = getCurrentTimeMs();
}

void Timer::stop(){
	m_endTimeMs = getCurrentTimeMs();
	updateIntervals();
}

void Timer::updateIntervals(){
	int intervalMs = m_endTimeMs - m_startTimeMs;
	m_intervals.push_back(intervalMs);
}

void Timer::print(){
	printAverageInterval();
}

void Timer::printAverageInterval(){
	int averageIntervalMs = accumulate(m_intervals.begin(), m_intervals.end(), 0.0)/m_intervals.size();
	std::cout << "Average interval: " << std::to_string(averageIntervalMs).substr(0, 5) << "ms" << std::endl;
}

void Timer::reset(){
	m_startTimeMs = 0;
	m_endTimeMs = 0;
	m_intervals.clear();
}

int Timer::getCurrentTimeMs(){
	return EM_ASM_INT({
		return Date.now();
	});
}