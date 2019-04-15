#ifndef WALKTOSUBTASK_H_INCLUDED
#define WALKTOSUBTASK_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <stdexcept>
#include <string>
#include <vector>          // std::vector
#include "Utils.h"
#include "Position.h"
#include "Subtask.h"
#include "TaskManager.h"
#include "GlobalTimer.h"
#include "Character.h"
#include "Compositor.h"
#include "Action.h"


class WalkAction : public Action
{
    public: 
        WalkAction() : Action("Walk") {}
};

class WalkToSubtask : public Subtask
{
    public:

     /** param walkAnimation A function which update the picture 
                             of the character every frame.
                             when it is called it is guaranteed 
                             that the character lock was acquired
                             and will be unlocked after the call.
                             So yo don't have to bother about this*/
     WalkToSubtask(PluginList* pluginList,
                        int id,
                        std::string eventName,
                        int characterId,
                        Position targetPosition,
                        double speed,
                        void (*walkAnimation) (Position sourcePosition, 
                                               Position targetPosition,
                                               int totalElapsedTicks, 
                                               int elapsedTicks)
                        );

     ~WalkToSubtask();

     virtual void process();
     void trySolveCollision(double totalElapsedTicks, 
                       double totalTicks, 
                       double elapsedTicks);

     /** pointer to the taskManager to pause tasks*/
     TaskManager* taskManager;

     GlobalTimer* timer;
     int maxTicks;
     Position targetPosition;
     Position sourcePosition;
     std::shared_ptr<Character> character;
     std::string eventName;
     double speed;

     void (*walkAnimation) (Position sourcePosition,
                            Position targetPosition,
                            int totalElapsedTicks, 
                            int elapsedTicks);

     std::shared_ptr<Action> walkAction;

};

#endif // WALKTOSUBTASK_H_INCLUDED
