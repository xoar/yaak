#ifndef CHOICESUBTASK_H
#define CHOICESUBTASK_H

#include "Position.h"
#include "Color.h"
#include "MessageSubtaskInterface.h"
#include "TaskManagerInterface.h"
#include "TriggerSubtaskInterface.h"
#include "TriggerZoneEntityInterface.h"
#include "WaitOnInputSubtaskInterface.h"
#include "WalkToSubtaskInterface.h"
#include "CharacterInterface.h"
#include "EventSystemInterface.h"
#include "MessageYobjectInterface.h"

#ifdef __cplusplus
extern "C" 
{
#endif

int ChoiceTryToLockCharacter(int id, 
                              const char* eventName,
                              void * pluginList );

void ChoiceBuildMessage(int * currentPosX, 
                        int* currentPosY,
                        MessageYobjectStructPtr* message,
                        TriggerZoneStructPtr* zone,
                        const char * zoneName,
                        const char * text,
                        int subtaskId,
                        void * pluginList
                        );


void ChoiceFinish(void * pluginList,int characterId);

#ifdef __cplusplus
}
#endif

#endif