#include "TestPlugin.h"

/* to walking around*/
#include "WalkEvent.h"

/*set the globals*/
#include "InitGlobals.h"

Event InitScene2
{

    InitGlobals();

    /*kill all threads*/
    KillAllTasksExcept(pluginList,"InitScene2");
    SceneFreeList(pluginList);
    ColliderFreeList(pluginList);
    TriggerZoneFreeList(pluginList);
    CompositorFreeList(pluginList);

    printf("build Room\n");

    Character Room2
      picture "standing":  "../res/Room2.png"
      position: 0, 0

    Character Bernard
      picture "standing right" : "../res/C1WR2.png"
      picture "standing left" : "../res/C1WL2.png"

      position : 300, 200

      animation "walking right":  "../res/C1WR1.png",
                                  "../res/C1WR2.png",
                                  "../res/C1WR3.png",
                                  "../res/C1WR2.png"

      animation "walking left": "../res/C1WL1.png",
                                "../res/C1WL2.png",
                                "../res/C1WL3.png",
                                "../res/C1WL2.png"

      animation "walking up": "../res/C1WU1.png",
                              "../res/C1WU2.png",
                              "../res/C1WU3.png",
                              "../res/C1WU2.png"
                                
      animation "walking down": "../res/C1WD1.png",
                                "../res/C1WD2.png",
                                "../res/C1WD3.png",
                                "../res/C1WD2.png"


    /*add a fix collider for bernard*/
    int CharacterId = CharacterGetId(pluginList,"Bernard");
    CharacterSetCollider(pluginList,CharacterId,20,20,230);
    CharacterSetWalkAnimationFkt(pluginList,CharacterId,walkAnimation);

    trigger WalkEvent

}

/*void reloadInit(void* _pluginList,void *_renderer)
{

    buildRefs(_pluginList,_renderer);

    AddTaskForNextRound(pluginList,"InitScene2", &InitScene2 );
}

void signalPluginReload()
{
    SceneFreeList(pluginList);
    TriggerZoneFreeList(pluginList);
    ColliderFreeList(pluginList);
    CompositorFreeList(pluginList);
}*/