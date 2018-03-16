#ifndef AABBCOLLIDERYOBJECT_H
#define AABBCOLLIDERYOBJECT_H

#include <iostream>
#include <SDL.h>

#include <stdexcept>
#include <string>

#include "Utils.h"
#include "Position.h"
#include "Rectangle.h"
#include "PluginList.h"

#include "ColliderYobject.h"
#include "RenderableYobject.h"
#include "GlobalSettings.h"


/*TODO: change thsi to AABB collider.
Do we need a collider superclass with isPoint in collider,
registering, collides with AABB?*/ 
class AABBColliderYobject: public ColliderYobject,
                           public RenderableYobject
{
    public:
        AABBColliderYobject(int id,int parentId,PluginList* pluginList);

        virtual ~AABBColliderYobject();

        Rectangle getRectangle();
        void setRectangle(Rectangle rec);
        void setRectangle(int x, int y, int width, int height);
        
        virtual void registerYobject(std::shared_ptr<AABBColliderYobject> yobject);
        virtual void unregisterYobject(std::shared_ptr<AABBColliderYobject> yobject);

        void setPosition(int x, int y);
        void setSize(int width, int height);

        bool isPointInCollider(Position point);
        bool collidesWith(std::shared_ptr<ColliderYobject> collider);

        virtual void render();

    protected:
        int posX;
        int posY;
        int width;
        int height;

        GlobalSettings* globalSettings;

    private:
};

#endif // AABBCOLLIDERYOBJECT_H
