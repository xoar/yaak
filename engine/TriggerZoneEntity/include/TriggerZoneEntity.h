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
#include "Yobject.h"


/*TODO: merge with AABB collider.*/
/*TODO:  implement onClick and onCollision Listener*/
/*TODO: implement a processFunction in TriggerZonePlugin*/

class TriggerZoneEntity: public Yobject
{
    public:
        TriggerZoneEntity(int id,std::string name,
                  PluginList* pluginList);

        virtual ~TriggerZoneEntity();

        Rectangle getRectangle();
        void setRectangle(Rectangle rec);
        void setRectangle(int x, int y, int width, int height);

        bool isPointInTriggerZone(Position point);

        void setOnClickListener() {};
        void setOnCollisionListener(){};

    protected:
        int posX;
        int posY;
        int width;
        int height;

        TriggerZonePlugin* triggerZonePlugin;

    private:
};

#endif // TRIGGERZONEENTITY_H
