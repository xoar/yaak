#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SDL.h>

#include <stdexcept>
#include <string>

#include "Utils.h"
#include "Yobject.h"

/* An entity is a Yobject bound to a name*/

class Entity : public Yobject
{
    public:
        Entity(int id,std::string name);
        virtual ~Entity() {};

        std::string getName();

    protected:

        std::string name;

};

#endif // ENTITY_H
