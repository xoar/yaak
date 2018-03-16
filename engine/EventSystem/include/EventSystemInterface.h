#ifndef EVENTSYSTEMINTERFACE_H
#define EVENTSYSTEMINTERFACE_H

#include "GameEvents.h"

#ifdef __cplusplus
extern "C" 
{
#endif

GameEvents EventSystemGetCurrentEvents(void* pluginList);


#ifdef __cplusplus
}
#endif

#endif