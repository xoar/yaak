#include "AABBColliderYobject.h"
#include "SDL.h"

AABBColliderYobject::AABBColliderYobject (int id,
                                          int parentId,
                                          PluginList* pluginList)
                                           :ColliderYobject(id,parentId,"AABB",pluginList),
                                            RenderableYobject(id,parentId,pluginList)
{
    posX = 0;
    posY = 0;
    width = 0;
    height = 0;

    try 
    { 
        /*used to check if we want debug frames*/
        globalSettings = (GlobalSettings*) pluginList->get(GlobalSettings::getPluginName());
    }
    catch(std::runtime_error& e)
    {
        std::cerr << e.what() <<" \n";
    }

}

void AABBColliderYobject::registerYobject(std::shared_ptr<AABBColliderYobject> yobject)
{
    /*TODO:WORKAROUND */
    RenderableYobject::registerYobject(std::static_pointer_cast<RenderableYobject>(yobject));
    ColliderYobject::registerYobject(std::static_pointer_cast<ColliderYobject>(yobject));
}

void AABBColliderYobject::unregisterYobject(std::shared_ptr<AABBColliderYobject> yobject)
{
    RenderableYobject::unregisterYobject(std::static_pointer_cast<RenderableYobject>(yobject));
    ColliderYobject::unregisterYobject(std::static_pointer_cast<ColliderYobject>(yobject));
}

AABBColliderYobject::~AABBColliderYobject()
{

}

void AABBColliderYobject::render()
{
    union SettingsValue debugFrames = globalSettings->getSetting("DebugFrames");
    if (debugFrames.intValue)
    {

        SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);

        SDL_Rect rect;
        rect.w = width;
        rect.h = height;
        rect.x = posX;
        rect.y = posY;

        SDL_RenderDrawRect(renderer,&rect);

        /* set the color back to black*/
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    }
}

Rectangle AABBColliderYobject::getRectangle()
{
    Rectangle rec;
    rec.posX = this->posX;
    rec.posY = this->posY;
    rec.width = this->width;
    rec.height = this->height;
    return rec;
    
}

void AABBColliderYobject::setRectangle(Rectangle rec)
{
    setRectangle(rec.posX,rec.posY,rec.width,rec.height);
}
void AABBColliderYobject::setRectangle(int x, int y, int width, int height)
{
    setPosition(x,y);
    setSize(width,height);
}


void AABBColliderYobject::setPosition(int x, int y)
{
    this->posX = x;
    this->posY = y;
}

void AABBColliderYobject::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

bool AABBColliderYobject::isPointInCollider(Position point)
{

    if( (point.posX >= this->posX) && (point.posX <= (this->posX + this->width)) &&
        (point.posY >= this->posY) && (point.posY <= (this->posY + this->height)) ) 
    {

        return true;
    }

    return false;
    
}


bool AABBColliderYobject::collidesWith(std::shared_ptr<ColliderYobject> collider)
{
	/*TODO support this*/
	return false;

}
