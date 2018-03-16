#include "EventSystemInterface.h"
#include "EventSystem.h"

GameEvents EventSystemGetCurrentEvents(void* pluginList)
{
    EventSystem* eventSys = (EventSystem*) ((PluginList*) pluginList)->get( EventSystem::getPluginName());
    return eventSys->getCurrentEvents();

}