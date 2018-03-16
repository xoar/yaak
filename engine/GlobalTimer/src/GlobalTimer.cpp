#include "GlobalTimer.h"

GlobalTimer::GlobalTimer()
{
    timer = new Timer();
    timer->start();

    elapsedTicks = 0;
}

GlobalTimer::~GlobalTimer()
{
    delete timer;
}


/** update the elapsed ticks. is called from the game loop*/
void GlobalTimer::updateTime()
{
    elapsedTicks = timer->elapsedTicks();
}

int GlobalTimer::getTicksForCurrentFrame()
{
    return elapsedTicks;
}
