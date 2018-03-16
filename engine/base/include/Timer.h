#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <stdexcept>
#include <string>

class Timer
{
    public:
    Timer();

    /** start the timer */
    void start();

    /** return the elapsed ticks since the last call of this function */
    int elapsedTicks();

    protected:

    int currentTick;
    int oldTick;

    int startTick;
};






#endif // TIMER_H_INCLUDED
