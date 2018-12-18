#ifndef COLLIDERPLUGIN_H
#define COLLIDERPLUGIN_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Utils.h"
#include "YobjectContainer.h"
#include "ColliderYobject.h"

#define COLLIDERPLUGINNAME ("ColliderPlugin")

class ColliderYobject;


/*TODO: add a procces function for the onClick and OnCollissionCollider*/
class ColliderPlugin: public YobjectContainer
{
public:
    virtual std::string getName() {return getPluginName();}
    static std::string getPluginName() {return COLLIDERPLUGINNAME;}

    //check if it collide with other collider
    bool collides(std::shared_ptr<ColliderYobject> collider)
    {
    	std::lock_guard<std::recursive_mutex> lock(containerMutex);
        
        for (auto it = yobjectList->begin();it != yobjectList->end(); it++)
        {
        	std::shared_ptr<ColliderYobject> someCollider = std::static_pointer_cast<ColliderYobject>((*it));
        	if (collider != someCollider)
            {
            	if (someCollider->collidesWith(collider))
                {
                    std::cout << "\ncollision from: "  << someCollider->getType()
                              << " with id: "        << someCollider->getId()
                              << " with parent id: " << someCollider->getParentId()
                              << "\n"
                              << " with collider: "  << collider->getType()
                              << " with id: "        << collider->getId()
                              << " with parent id: " << collider->getParentId()
                              << "\n";
                	return true;
                }
           	}
        }

        return false;
    }
};

#endif