#ifndef COLLIDERYOBJECT_H
#define COLLIDERYOBJECT_H

#include <iostream>
#include <SDL.h>

#include <stdexcept>
#include <string>

#include "Utils.h"
#include "Position.h"
#include "Rectangle.h"
#include "PluginList.h"

#include "Yobject.h"
#include <memory>

class ColliderPlugin;


/*TODO: fix the himself as a parameter stuff in collides*/
class ColliderYobject: public Yobject
{
    public:
        ColliderYobject(int id,int parentId,std::string type,PluginList* pluginList);

        virtual ~ColliderYobject();

        virtual void registerYobject(std::shared_ptr<ColliderYobject> yobject);
        virtual void unregisterYobject(std::shared_ptr<ColliderYobject> yobject);

        virtual bool isPointInCollider(Position point);
        virtual bool collidesWith(std::shared_ptr<ColliderYobject> collider);
        
        /* checks if a collision occurs. must have themself as a parameter for now*/
        bool collides();
        
        /* return a list of the colliders from the collision.*/
        //vector<std::shared_ptr<ColliderYobject>> getCollisionList();

        std::string getType();

    protected:
        /*other objects can check if they have a collide routin for this type*/
        std::string type;

        ColliderPlugin* colliderPlugin;

    private:
};

#endif // COLLIDERYOBJECT_H
