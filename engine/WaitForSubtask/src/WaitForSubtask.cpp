#include "WaitForSubtask.h"
#include <stdexcept>

WaitForSubtask::WaitForSubtask(PluginList* pluginList,
                        int id,
                        std::string eventName)
                        : Subtask(id)
{

    elapsedTicks = 0;
    this->eventName = eventName;
    
    GlobalSettings* globalSettings = nullptr;
    try 
    { 
        /*get the default time and configure the maxticks with it*/
        globalSettings = (GlobalSettings*) pluginList->get(GlobalSettings::getPluginName());
    }
    catch(std::runtime_error& e)
    {
        std::cerr <<"ERROR: Cant find the global Settings, subtask id: "<< id 
        << ", "  << e.what() <<" \n";
    }

    union SettingsValue defaultTime = globalSettings->getSetting("DefaultTime");
    /*set the max ticks*/
    this->setTime(defaultTime.doubleValue);

    /*try to assign the global timer */
    try 
    { 
        this->timer = (GlobalTimer*) pluginList->get(GlobalTimer::getPluginName()); 
    }
    catch(std::runtime_error& e)
    {
    /* for some reasons, the node cant access the global timer */
        std::cerr <<"ERROR: Cant find the global timer, subtask id: "<< id 
        << ", "  << e.what() <<" \n";
    }

    try 
    { 
        this->taskManager = ((TaskManager*) pluginList->get(TaskManager::getPluginName()));
    }
    catch(std::runtime_error& e)
    {
    /* for some reasons, the node cant access the task manager */
        std::cerr <<"ERROR: Cant find the task manager, subtask id: "<< id 
        << ", "  << e.what() <<" \n";
    }

}

/** this is the process function which must be overriden
    to implement the disired functionality */
void WaitForSubtask::process()
{

    while(elapsedTicks <= maxTicks)
    {
        
        taskManager->suspendTaskUntilNextRound(eventName);

        elapsedTicks += timer->getTicksForCurrentFrame();
        //std::cout << "Subtask: " << id  <<" elapsed time: " << elapsedTicks  <<std::endl;

    }

    elapsedTicks = 0;

}


void WaitForSubtask::setTime(double time)
{
    this->maxTicks = time*1000;
}
