#ifndef GLOBALTIMER_H
#define GLOBALTIMER_H

#include "Utils.h"
#include "Timer.h"
#include "GameEnginePlugin.h"

#define GLOBALTIMERNAME ("GlobalTimer")

class GlobalTimer : public GameEnginePlugin
{
    public:
        /** update the actual elapsed Ticks for the current frame*/
        virtual void updateTime();
        /**get the elapsed time for this current frame.
         * is updated via process in the main game loop
         */
        int getTicksForCurrentFrame();

        GlobalTimer();
        virtual ~GlobalTimer();

        virtual std::string getName() {return getPluginName();}
        static std::string getPluginName() {return GLOBALTIMERNAME;}
    private:
        Timer* timer;
        /** The elapsed Ticks for thie current frame*/
        int elapsedTicks;

};



#endif // GLOBALTIMER_H
