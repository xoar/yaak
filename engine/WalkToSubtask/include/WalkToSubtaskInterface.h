#ifndef WALKTOSUBTASKINTERFACE_H_INCLUDED
#define WALKTOSUBTASKINTERFACE_H_INCLUDED

#include "Position.h"

#ifdef __cplusplus
extern "C" 
{
#endif


/*foward the declaration. definition is done in the corresponding c file*/
struct WalkToStruct ;

typedef struct WalkToStruct * WalkToStructPtr;

WalkToStructPtr WalkToConstructor(void* pluginList,
                                  int id,
                                  const char* eventName,
                                  int characterId,
                                  Position targetPosition,
                                  double speed,
                                  void (*walkAnimation) (Position sourcePosition, 
                                                         Position targetPosition,
                                                         int totalElapsedTicks, 
                                                         int elapsedTicks));

WalkToStructPtr WalkToConstructor2I(void* pluginList,
                                  int id,
                                  const char* eventName,
                                  int characterId,
                                  int targetPositionX,
                                  int targetPositionY,
                                  double speed,
                                  void (*walkAnimation) (Position sourcePosition, 
                                                         Position targetPosition,
                                                         int totalElapsedTicks, 
                                                         int elapsedTicks));

int WalkToProcess(WalkToStructPtr subtask);
void WalkToDestructor(WalkToStructPtr subtask);

#ifdef __cplusplus
}
#endif

#endif