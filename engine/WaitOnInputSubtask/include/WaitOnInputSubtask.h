#ifndef WAITONINPUTSUBTASK_H_INCLUDED
#define WAITONINPUTSUBTASK_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <stdexcept>
#include <string>
#include <vector>          // std::vector
#include "Utils.h"
#include "Subtask.h"
#include "TaskManager.h"
#include "EventSystem.h"

class WaitOnInputSubtask : public Subtask
{
    public:
     WaitOnInputSubtask(PluginList* pluginList,
                        int id,
                        std::string eventName,
                        std::string device,
                        std::string specifier);

     virtual void process();

     EventSystem* eventSys;

     std::string device;
     std::string specifier;

    /** pointer to the taskManager to pause tasks*/
    TaskManager* taskManager;

    std::string eventName;

};

#endif // WAITONINPUTSUBTASK_H_INCLUDED
