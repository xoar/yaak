#include "Timer.h"

Timer::Timer()
{
    this->currentTick = 0;
    this->oldTick = 0;
    this->startTick = 0;

}

/** start the timer */
void Timer::start()
{
    startTick = SDL_GetTicks();
    currentTick = startTick;

}

/** return the elapsed time since the last call of this function */
int Timer::elapsedTicks()
{
    int result;

    currentTick = SDL_GetTicks();
    result = currentTick - oldTick;

    oldTick = currentTick;

    return result;
}
