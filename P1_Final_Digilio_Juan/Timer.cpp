#include "Timer.h"

Timer::Timer()
{
    lastTime = high_resolution_clock::now();
}

Timer::~Timer()
{
}

bool Timer::ElapsedTime(int interval)
{ 
    auto currentTime = high_resolution_clock::now();
    auto deltaTime = duration_cast<milliseconds>(currentTime - lastTime).count();

    if (deltaTime >= interval)
    {
        lastTime = currentTime;
        return true;
    }

    return false; 
}
