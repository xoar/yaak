#include "Entity.h"

Entity::Entity(int id,std::string name) : Yobject(id,0)
{
    this->name = name;
    this->type = "Entity";
}

std::string Entity::getName()
{
    return name;
}