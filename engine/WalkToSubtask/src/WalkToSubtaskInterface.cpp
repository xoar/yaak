#include "WalkToSubtaskInterface.h"
#include "WalkToSubtask.h"

/*define the struct. Just a wrapper for the cpp object*/
struct WalkToStruct{
    WalkToSubtask* subtask;
};

WalkToStructPtr WalkToConstructor(void* pluginList,
                                  int id,
                                  const char* eventName,
                                  int characterId,
                                  Position targetPosition,
                                  double speed,
                                  void (*walkAnimation) (Position sourcePosition, 
                                                         Position targetPosition,
                                                         int totalElapsedTicks, 
                                                         int elapsedTicks))
{
    WalkToStructPtr subtask  =  (WalkToStructPtr) malloc(sizeof(struct WalkToStruct));
    
    subtask->subtask = new WalkToSubtask((PluginList*) pluginList,
                                          id,
                                          std::string(eventName),
                                          characterId,
                                          targetPosition,
                                          speed,
                                          walkAnimation
                                         );
    return subtask;

}

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
                                                         int elapsedTicks))
{
  Position p = { targetPositionX,targetPositionY};
  return WalkToConstructor(pluginList,id,eventName,characterId,p,speed,walkAnimation);

}

int WalkToProcess(WalkToStructPtr subtask)
{
    try
    {
      subtask->subtask->process();
    }
    catch (KillException& e)
    {
        /* if a kill was signaled return this
           to the caller so the thread can terminate*/
        
        /*free the ressource 
          because it was a heap allocation its not done automatically*/
        std::cout << "WalkTo recive kill signal"<< std::endl;
        WalkToDestructor(subtask);
        return 0;
    }

    /*normal exit without a reload*/
    WalkToDestructor(subtask);
    return 1;
}

void WalkToDestructor(WalkToStructPtr subtask)
{
    delete subtask->subtask;
    free(subtask);
}