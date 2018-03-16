#ifndef TRIGGERZONEENTITY_H
#define TRIGGERZONEENTITY_H

#include <iostream>
#include <SDL.h>

#include <stdexcept>
#include <string>

#include "Utils.h"
#include "Position.h"
#include "Rectangle.h"
#include "PluginList.h"
#include "TriggerZonePlugin.h"
#include "Entity.h"

class TriggerZoneEntity: public Entity
{
    public:
        TriggerZoneEntity(int id,std::string name,
                  PluginList* pluginList);

        virtual ~TriggerZoneEntity();

        Rectangle getRectangle();
        void setRectangle(Rectangle rec);
        void setRectangle(int x, int y, int width, int height);

        bool isPointInTriggerZone(Position point);

    protected:
        int posX;
        int posY;
        int width;
        int height;

        TriggerZonePlugin* triggerZonePlugin;

    private:
};

#endif // TRIGGERZONEENTITY_H
