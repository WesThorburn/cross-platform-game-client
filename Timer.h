#ifndef TIMER_H
#define TIMER_H

#include <vector>

class Timer{
public:
	Timer();
	void start();
	void stop();
	void print();
protected:
	std::vector<int> m_intervals = {};
	
	void reset();
private:
	int m_startTimeMs = 0, m_endTimeMs = 0;

	void updateIntervals();
	void printAverageInterval();
	int getCurrentTimeMs();
};

#endif