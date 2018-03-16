#include "SceneEntity.h"

SceneEntity::SceneEntity(int id,
                         std::string name,
                          PluginList* pluginList)
                          : SceneYobject(id,0,pluginList)
{
    this->name = name;
    this->type = "Entity";
}

SceneEntity::~SceneEntity()
{
    //dtor
}

std::string SceneEntity::getName()
{
    return name;
}