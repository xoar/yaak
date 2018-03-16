#include "WaitOnInputSubtask.h"

WaitOnInputSubtask::WaitOnInputSubtask(PluginList* pluginList,
                        int id,
                        std::string eventName,
                        std::string device,
                        std::string specifier)
                        : Subtask(id)
{
    this->device = device;
    this->specifier = specifier;
    eventSys = (EventSystem*) pluginList->get( EventSystem::getPluginName());

    taskManager = ((TaskManager*) pluginList->get(TaskManager::getPluginName()));

    if (taskManager  == nullptr)
    {
    /* for some reasons, cant access the task manager */
        std::cerr <<"Cant find the task manager, needed for the runconceperloop subtask\n";
    }

    this->eventName = eventName;
}

/** just fire the next node */
void WaitOnInputSubtask::process()
{
    bool subtaskDone = false;

    while(!subtaskDone)
    {

        GameEvents events = eventSys->getCurrentEvents();

        if (device == "mouse")
        {
            if (specifier == "left")
            {
                //std::cout << "WaitOnInput: check mouse \n";
                if (events.leftMouseButtonPressed)
                {
                    std::cout << "WaitOnInput: left button pressed \n";
                    subtaskDone = true;
                }
            }
            else if (specifier == "right")
                if (events.rightMouseButtonPressed)
                    subtaskDone = true;
            else if (specifier == "moved")
                if (events.mouseMoved)
                    subtaskDone = true;
        }

        /*blocks unitl next round*/
        if (!subtaskDone)
        {
            taskManager->suspendTaskUntilNextRound(eventName);
        }
    }

}
