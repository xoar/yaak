#ifndef SEGMENTCOLLIDERINTERFACE_H
#define SEGMENTCOLLIDERINTERFACE_H

#include "Position.h"
#include "Rectangle.h"
#include "Size.h"

#ifdef __cplusplus
extern "C" 
{
#endif

/*foward the declaration. definition is done in the corresponding c file*/
struct SegmentColliderStruct ;

typedef struct SegmentColliderStruct * SegmentColliderStructPtr;

SegmentColliderStructPtr SegmentColliderConstructor(int id,
                                                    void* pluginList);

void SegmentColliderFreePointerStruct(SegmentColliderStructPtr collider);

void SegmentColliderSetSegment(SegmentColliderStructPtr collider,
                                   int startX, int startY, int endX, int endY);

#ifdef __cplusplus
}
#endif

#endif

