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

Start Event UnitTest1
{
        /*TODO: add a Unit test without INIT GLobals*/
        InitGlobals();

        Scene Object PurpursRoom
        picture "standing":  "../res/purpurRoom2.png"
        position : 0, 0

        int CharacterId = CharacterGetId(pluginList,"PurpursRoom");
        CharacterSetRenderPriority(pluginList,CharacterId,0);
        CharacterDeactivateCollider(pluginList,CharacterId);

        Scene Object TriggerZone
        position : 227, 0
        picture "right": "../res/zone.png"
        display: "zone"

        Scene Object TriggerZone2
        position : 227, 200
        picture "right": "../res/zone.png"
        display: "zone2"

        /*create Bernard*/
        Character Bernard
        picture "standing right" : "../res/C1WR2.png"
        picture "standing left" : "../res/C1WL2.png"

        position : 300, 50
        display: "Bernie"

        /*add a fix collider for bernard*/
        CharacterId = CharacterGetId(pluginList,"Bernard");
        CharacterSetWalkCollider(pluginList,CharacterId,20,20,230);
        CharacterSetWalkAnimationFkt(pluginList,CharacterId,walkAnimation);

        wait on left mouse click

        
        CharacterId = CharacterGetId(pluginList,"TriggerZone");

        printf("\nTest collision: Zone with somebody\n");

        if (CharacterCurrentPictureCollides(pluginList,CharacterId,"",""))
        {
            /*trigger InitScene2*/
            printf("collides");
        }
        else
            printf("not collides");


        printf("\nTest collision: Bernies walkcollider with somebody\n");

        CharacterId = CharacterGetId(pluginList,"Bernard");

        if (CharacterWalkColliderCollides(pluginList,CharacterId,"",""))
        {
            /*trigger InitScene2*/
            printf("collides\n");
        }
        else
            printf("not collides\n");

        printf("\nTest collision: Zone 2 with somebody\n");

        CharacterId = CharacterGetId(pluginList,"TriggerZone2");

        if (CharacterCurrentPictureCollides(pluginList,CharacterId,"",""))
        {
            /*trigger InitScene2*/
            printf("collides\n");
        }
        else
            printf("not collides\n");

        printf("\nTest collision: Zone 2 with walkCollider\n");

        if (CharacterCurrentPictureCollides(pluginList,CharacterId,"","WalkCollider"))
        {
            /*trigger InitScene2*/
            printf("collides\n");
        }
        else
            printf("not collides\n");





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