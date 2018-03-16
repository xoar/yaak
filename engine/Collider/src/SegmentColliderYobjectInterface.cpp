#include "SegmentColliderYobjectInterface.h"
#include "SegmentColliderYobject.h"
#include <memory>

/*define the struct. Just a wrapper for the cpp object*/
struct SegmentColliderStruct{
    std::shared_ptr<SegmentColliderYobject> collider;
};

/*its Constructor*/
SegmentColliderStructPtr SegmentColliderConstructor(int id,
                                                    void* pluginList)
{
    SegmentColliderStructPtr collider  =  new SegmentColliderStruct();
    
    collider->collider = std::make_shared<SegmentColliderYobject>(
                                          id,
                                          0,
                                          (PluginList*) pluginList
                                          );
    collider->collider->registerYobject(collider->collider);
    return collider;

}

void SegmentColliderFreePointerStruct(SegmentColliderStructPtr collider)
{
    collider->collider.reset();
    free(collider);
}


void SegmentColliderSetSegment(SegmentColliderStructPtr collider,
                                   int startX, int startY, int endX, int endY)
{

    collider->collider->setSegment(startX, startY, endX, endY);
}
