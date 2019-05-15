#include "TestPlugin.h"

/* to walking around*/
#include "WalkEvent.h"

/*set the globals*/
#include "InitGlobals.h"


/*signal the plugin was reloaded*/
int wasReloaded = 0;

/*the door status*/
int isDoorOpen = 0;


int HeyTentacle = 0;

int BernardIsInTheRoom = 0;

Event EndlessTest
{
    int a;
    int CharacterId = CharacterGetId(pluginList,"TriggerZone");
    trigger EndlessTest;
}


Start Event UnitTest1
{

        Scene Object PurpursRoom
        picture "standing":  "../res/purpurRoom2.png"
        position : 0, 0

        int CharacterId = CharacterGetId(pluginList,"PurpursRoom");
        CharacterSetRenderPriority(pluginList,CharacterId,0);
        CharacterDeactivateCollider(pluginList,CharacterId);

        Scene Object TriggerZone
        position : 227, 0
        picture "right": "../res/zone.png"

        /*create Bernard*/
        Character Bernard
        picture "standing right" : "../res/C1WR2.png"
        picture "standing left" : "../res/C1WL2.png"

        position : 300, 50

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
        CharacterId = CharacterGetId(pluginList,"Bernard");
        CharacterSetCollider(pluginList,CharacterId,20,20,230);
        CharacterSetWalkAnimationFkt(pluginList,CharacterId,walkAnimation);

        CharacterId = CharacterGetId(pluginList,"TriggerZone");
        if (CharacterCollides(pluginList,CharacterId))
        {
            /*trigger InitScene2*/
            printf("collides\n");
        }
        else
            printf("not collides\n");

        trigger EndlessTest

}

void reloadInit(void* _pluginList,void *_renderer)
{

    /* thats not good. we loaded the plugin again*/

    SceneFreeList(_pluginList);
    TriggerZoneFreeList(_pluginList);
    ColliderFreeList(_pluginList);
    CompositorFreeList(_pluginList);

    buildRefs(_pluginList,_renderer);

    wasReloaded = 1;

    AddTaskForNextRound(pluginList,"UnitTest1", &UnitTest1 );
}

void signalPluginReload()
{
    /** kill all stuff*/
    SceneFreeList(pluginList);
    TriggerZoneFreeList(pluginList);
    ColliderFreeList(pluginList);
    CompositorFreeList(pluginList);

    /*if i kill things here the waked up functions try to acess stuff before
      clean themself*/
}