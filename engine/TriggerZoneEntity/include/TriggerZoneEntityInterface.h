#ifndef TRIGGERZONEENTITYINTERFACE_H
#define TRIGGERZONEENTITYINTERFACE_H

#include "Position.h"
#include "Rectangle.h"

#ifdef __cplusplus
extern "C" 
{
#endif

/*foward the declaration. definition is done in the corresponding c file*/
struct TriggerZoneStruct ;

typedef struct TriggerZoneStruct * TriggerZoneStructPtr;


TriggerZoneStructPtr TriggerZoneConstructor(int id,const char* name,
                      void* pluginList);

/*free only the pointer strcut. not deallocate the c++ object*/
void TriggerZoneFreePointerStruct(TriggerZoneStructPtr tiggerZone);

/* deallocate the c++ object and free the struct*/
void TriggerZoneDestructor(TriggerZoneStructPtr tiggerZone);


Rectangle TriggerZoneGetRectangle(TriggerZoneStructPtr tiggerZone);

void TriggerZoneSetRectangle(TriggerZoneStructPtr tiggerZone,
                             Rectangle rec);

void TriggerZoneSetRectangle4I(TriggerZoneStructPtr tiggerZone,
                             int x, int y, int width, int height);

int IsPointInTriggerZone(TriggerZoneStructPtr tiggerZone,
                          Position point);


#ifdef __cplusplus
}
#endif

#endif