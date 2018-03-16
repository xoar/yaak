#include "TriggerZoneEntityInterface.h"
#include "TriggerZoneEntity.h"

/*define the struct. Just a wrapper for the cpp object*/
struct TriggerZoneStruct{
    TriggerZoneEntity* triggerZone;
};

TriggerZoneStructPtr TriggerZoneConstructor(int id,const char* name,
                      void* pluginList)
{
    TriggerZoneStructPtr triggerZone  =  (TriggerZoneStructPtr) malloc(sizeof(struct TriggerZoneStruct));
    
    triggerZone->triggerZone = new TriggerZoneEntity(
                                               id,
                                               std::string(name),
                                               (PluginList*) pluginList
                                               );
    return triggerZone;

}


Rectangle TriggerZoneGetRectangle(TriggerZoneStructPtr triggerZone)
{
    return triggerZone->triggerZone->getRectangle();
}

void TriggerZoneSetRectangle(TriggerZoneStructPtr triggerZone,
                             Rectangle rec)
{
    triggerZone->triggerZone->setRectangle(rec);
}

void TriggerZoneSetRectangle4I(TriggerZoneStructPtr triggerZone,
                             int x, int y, int width, int height)
{
    triggerZone->triggerZone->setRectangle(x,y,width,height);
}

int IsPointInTriggerZone(TriggerZoneStructPtr triggerZone,
                          Position point)
{
    return triggerZone->triggerZone->isPointInTriggerZone(point);
}

void TriggerZoneFreePointerStruct(TriggerZoneStructPtr triggerZone)
{
    free(triggerZone);
}

void TriggerZoneDestructor(TriggerZoneStructPtr triggerZone)
{
    delete triggerZone->triggerZone;
    free(triggerZone);
}