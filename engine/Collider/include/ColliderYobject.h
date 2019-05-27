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
        virtual bool collidesWith(std::shared_ptr<ColliderYobject> collider,std::string type,std::string tag);
        
        /* checks if a collision occurs. must have themself as a parameter for now*/
        bool collides(std::string type,std::string tag);
        
        /* return a list of the colliders from the collision.*/
        //vector<std::shared_ptr<ColliderYobject>> getCollisionList();

        std::string getType();

        /*set active for collision checks*/
        void setActive() { active = true;}
        void setInactive() { active = false;}

        bool isActive() { return active;}

        void setTag(std::string tag)
        {
            this->tag = tag;
        }

        std::string getTag()
        {
            return tag;
        }

    protected:
        /*other objects can check if they have a collide routin for this type*/
        std::string type;

        ColliderPlugin* colliderPlugin;

        bool active;

        std::string tag;

    private:
};

#endif // COLLIDERYOBJECT_H
