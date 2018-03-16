#include "RenderableEntity.h"

RenderableEntity::RenderableEntity(int id,
                                   std::string name,
                                   PluginList* pluginList)
                                   : RenderableYobject(id,0,pluginList)
{
    this->name = name;
    this->type = "Entity";
}

RenderableEntity::~RenderableEntity()
{
    //dtor
}

std::string RenderableEntity::getName()
{
    return name;
}
