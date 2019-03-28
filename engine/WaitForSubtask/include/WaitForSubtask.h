#ifndef WAITFOR_H_INCLUDED
#define WAITFOR_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <stdexcept>
#include <string>
#include "Utils.h"
#include "PluginList.h"
#include "Subtask.h"
#include "GlobalTimer.h"
#include "TaskManager.h"
#include "GlobalSettings.h"
#include <memory>

class WaitForSubtask : public Subtask
{
    public:
    WaitForSubtask(PluginList* pluginList,
                   int id,
                   std::string eventName);
    
    ~WaitForSubtask() {};

    /**wait for the specified time. blocks  */
    virtual void process();
    void setTime(double time);

    protected:

    /** pointer to the taskManager to pause tasks*/
    TaskManager* taskManager;

    GlobalTimer* timer;
    int elapsedTicks;
    int maxTicks;

    std::string eventName;

};

#endif // WAITFOR_H_INCLUDED
