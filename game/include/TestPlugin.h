#ifndef TESTPLUGIN_H_INCLUDED
#define TESTPLUGIN_H_INCLUDED

#include "stdio.h"
#include "Position.h"
#include "Color.h"
#include "MessageSubtaskInterface.h"
#include "TaskManagerInterface.h"
#include "CompositorInterface.h"
#include "TriggerSubtaskInterface.h"
#include "TriggerZoneEntityInterface.h"
#include "WaitOnInputSubtaskInterface.h"
#include "WaitForSubtaskInterface.h"
#include "WalkToSubtaskInterface.h"
#include "CharacterInterface.h"
#include "EventSystemInterface.h"
#include "MessageYobjectInterface.h"
#include "ChoiceSubtask.h"
#include "GlobalSettingsInterface.h"
#include "SegmentColliderYobjectInterface.h"

void* pluginList = 0;
void *renderer = 0;

void buildRefs(void* _pluginList,void* _renderer)
{

    /* if you use NULL you have a #comment spread over several lines*/
    if (_pluginList  == (void*) 0 )
    {
        printf("ERROR: Can't access the pluginList\n");
    }
    pluginList = _pluginList;

    if (_renderer  == (void*) 0 )
    {
        printf("ERROR: Can't access the renderer\n");
    }
    renderer = _renderer;
    
}



#ifdef __cplusplus
extern "C" 
{
#endif

void pluginInit (void* _pluginList,
                 void* _renderer);

void reloadInit(void* _pluginList,void *_renderer);

#ifdef __cplusplus
}
#endif

#endif
