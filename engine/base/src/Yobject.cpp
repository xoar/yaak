#include "Yobject.h"

Yobject::Yobject(int id,int parentId)
{
    this->id = id;
    this->parentId = parentId;
    this->type = "Yobject";
    name = "";
}

Yobject::Yobject(int id,std::string name): Yobject(id,0)
{
    this->type = "Entity";
    this->name = name;
}

int Yobject::getId()
{
    return id;
}

void Yobject::setId(int id)
{
    this->id = id;
}

int Yobject::getParentId()
{
    return parentId;
}

void Yobject::setParentId(int parentId)
{
    this->parentId = parentId;
}

/**set the object type. used as a leightwight rtti approach*/
void Yobject::setType(std::string type)
{
    this->type = type;
}

/**set the object type. used as a leightwight rtti approach*/
std::string Yobject::getType()
{
    return type;
}