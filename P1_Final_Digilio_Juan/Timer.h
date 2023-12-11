#pragma once

#include <chrono>


using namespace std;
using namespace chrono;

class Timer
{
private:

	time_point<high_resolution_clock> lastTime;


public:

	Timer();
	~Timer();

	bool ElapsedTime(int interval);
};

