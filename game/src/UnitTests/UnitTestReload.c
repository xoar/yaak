#include "TestPlugin.h"
/*set the globals*/
#include "InitGlobals.h"


/*signal the plugin was reloaded*/
int wasReloaded = 0;

Event EndlessTest
{
    int a;
    int CharacterId = CharacterGetId(pluginList,"TriggerZone");
    trigger EndlessTest;
}


Start Event UnitTest1
{

        Scene Object TriggerZone
            position : 227, 0
            picture "right": "../res/zone.png"

        Scene Object PurpursRoom
            picture "standing":  "../res/purpurRoom2.png"
            position : 0, 0


        //trigger EndlessTest

}

Event AfterReload
{
    printf("\nReload Successfull\n");

    Scene Object PurpursRoom
            picture "standing":  "../res/purpurRoom2.png"
            position : 0, 0


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

    AddTaskForNextRound(pluginList,"AfterReload", &AfterReload );
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