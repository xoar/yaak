#include "UsedPlugins.h"
#include "EngineUtils.h"

void initPlugins(void* _pluginList)
{
	//cast it to the right pointer
	PluginList* list = (PluginList* ) _pluginList;


	/**-------------- Main Plugins --------------------*/

    GameEnginePlugin* timer =  new GlobalTimer();
    list->add(timer);

    GameEnginePlugin* compositor =  new Compositor(list);
    list->add(compositor);

    GameEnginePlugin* eventSys = new EventSystem(list);
    list->add(eventSys);

    GameEnginePlugin* globalSettingsPlugin = new GlobalSettings();
    list->add(globalSettingsPlugin);

    //--------------------------------------------------

	GameEnginePlugin* colliderPlugin =  new ColliderPlugin();
    list->add(colliderPlugin);

    GameEnginePlugin* sceneContainer =  new SceneContainer();
    list->add(sceneContainer);

    GameEnginePlugin* triggerZonePlugin = new TriggerZonePlugin();
    list->add(triggerZonePlugin);

}

void mainLoop(void* _pluginList)
{

	//cast it to the right pointer
	PluginList* list = (PluginList* ) _pluginList;

    /*update the elapsed time*/
    ((GlobalTimer*) list->get( GlobalTimer::getPluginName() ))->updateTime();
    /* update the event queue*/
    ((EventSystem*) list->get( EventSystem::getPluginName() ))->process();

    /* unlock the context for using it in different threads*/
    ((Compositor*) list->get( Compositor::getPluginName() ))->InitContextSharing();

    /*process the user logic*/
    ((TaskManager*) list->get( TaskManager::getPluginName() ))->process();
    
    /* lock the context for using it alone*/
    ((Compositor*) list->get( Compositor::getPluginName() ))->FinalizeContextSharing();

    /* check if a reload of the plugin should be done*/
    bool reload = ((ReloadGamePlugin*) list->get( ReloadGamePlugin::getPluginName() ))->getReloadStatus();

    /* if there is a reload dont draw the scene(black) for better placing of objects*/
    if (!reload)
        /*render the scene*/
        ((Compositor*) list->get( Compositor::getPluginName() ))->renderYobjects();

}