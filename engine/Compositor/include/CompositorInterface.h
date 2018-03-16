#ifndef COMPOSITORINTERFACE_H
#define COMPOSITORINTERFACE_H

#ifdef __cplusplus
extern "C" 
{
#endif

void CompositorFreeList(void * pluginList);
void CompositorDeactivateAllYobjects(void * pluginList);
void CompositorRemoveAllEntities(void * pluginList);
/*TODO: WORKAROUND*/
void SceneFreeList(void * pluginList);
void TriggerZoneFreeList(void * pluginList);
void ColliderFreeList(void * pluginList);

#ifdef __cplusplus
}
#endif

#endif