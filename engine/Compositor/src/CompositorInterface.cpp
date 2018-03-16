#include "CompositorInterface.h"
#include "Compositor.h"
#include "PluginList.h"
#include "SceneContainer.h"
#include "TriggerZonePlugin.h"
#include "ColliderPlugin.h"

void CompositorFreeList(void * pluginList)
{
    PluginList* mPluginList = (PluginList*) pluginList;
    ((Compositor*) mPluginList->get( Compositor::getPluginName() ))->freeList();
}

void CompositorDeactivateAllYobjects(void * pluginList)
{
    PluginList* mPluginList = (PluginList*) pluginList;
    ((Compositor*) mPluginList->get( Compositor::getPluginName() ))->deactivateAllYobjects();
}

void CompositorRemoveAllEntities(void * pluginList)
{
    PluginList* mPluginList = (PluginList*) pluginList;
    ((Compositor*) mPluginList->get( Compositor::getPluginName() ))->deleteAllEntities();
}

/*TODO: WORKAROUND*/
void SceneFreeList(void * pluginList)
{
    PluginList* mPluginList = (PluginList*) pluginList;
    ((SceneContainer*) mPluginList->get( SceneContainer::getPluginName() ))->freeList();
}
void TriggerZoneFreeList(void * pluginList)
{
    PluginList* mPluginList = (PluginList*) pluginList;
    ((TriggerZonePlugin*) mPluginList->get( TriggerZonePlugin::getPluginName() ))->freeList();
}
void ColliderFreeList(void * pluginList)
{
    PluginList* mPluginList = (PluginList*) pluginList;
    ((ColliderPlugin*) mPluginList->get( ColliderPlugin::getPluginName() ))->freeList();
}