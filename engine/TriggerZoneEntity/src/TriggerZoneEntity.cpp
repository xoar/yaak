#include "TriggerZoneEntity.h"

TriggerZoneEntity::TriggerZoneEntity(int id,std::string name,
                     PluginList* pluginList)
                     : Yobject(id,name)
{
    posX = 0;
    posY = 0;
    width = 0;
    height = 0;

    /*add the trigger zone to the plugin list */
    triggerZonePlugin = (TriggerZonePlugin*) pluginList->get( TriggerZonePlugin::getPluginName());
    //TODO: add register/unregister function
    //triggerZonePlugin->addYobject(this);
}


TriggerZoneEntity::~TriggerZoneEntity()
{
    /*remove the yobject to the render queue*/
    //triggerZonePlugin->removeYobject(this);
}


void TriggerZoneEntity::setRectangle(Rectangle rec)
{
    this->posX = rec.posX;
    this->posY = rec.posY;
    this->width = rec.width;
    this->height = rec.height;
}

void TriggerZoneEntity::setRectangle(int x, int y, int width, int height)
{
    this->posX = x;
    this->posY = y;
    this->width = width;
    this->height = height;
}

Rectangle TriggerZoneEntity::getRectangle()
{
    Rectangle rec;
    rec.posX = this->posX;
    rec.posY = this->posY;
    rec.width = this->width;
    rec.height = this->height;
    return rec;
}

bool TriggerZoneEntity::isPointInTriggerZone(Position point)
{

    if( (point.posX >= this->posX) && (point.posX <= (this->posX + this->width)) &&
        (point.posY >= this->posY) && (point.posY <= (this->posY + this->height)) ) 
    {

        return true;
    }

    return false;

}