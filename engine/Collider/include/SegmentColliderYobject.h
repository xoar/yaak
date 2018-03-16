#ifndef SEGMENTCOLLIDERYOBJECT_H
#define SEGMENTCOLLIDERYOBJECT_H

#include <iostream>
#include <SDL.h>

#include <stdexcept>
#include <string>

#include "Utils.h"
#include "Position.h"
#include "Rectangle.h"
#include "PluginList.h"
#include "ColliderYobject.h"
#include "AABBColliderYobject.h"
#include "RenderableYobject.h"
#include "GlobalSettings.h"

class SegmentColliderYobject: public ColliderYobject,
                              public RenderableYobject
{
    public:
        SegmentColliderYobject(int id,int parentId,PluginList* pluginList);

        virtual ~SegmentColliderYobject();

        virtual void registerYobject(std::shared_ptr<SegmentColliderYobject> yobject);
        virtual void unregisterYobject(std::shared_ptr<SegmentColliderYobject> yobject);

        void setSegment(int startX,int startY,int endX,int endY);
        bool isPointInCollider(Position point);
        bool collidesWith(std::shared_ptr<ColliderYobject> collider);
        Vector getNormal();

        virtual void render();

    protected:
        int TestSegmentAABB(Point p0, 
                            Point p1, 
                            Rectangle aabb);

        Point start;
        Point end;

        Vector normal;

        GlobalSettings* globalSettings;
};

#endif // SEGMENTCOLLIDERYOBJECT_H
