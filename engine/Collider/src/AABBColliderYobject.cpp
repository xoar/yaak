#include "AABBColliderYobject.h"
#include "SDL.h"

AABBColliderYobject::AABBColliderYobject (int id,
                                          int parentId,
                                          PluginList* pluginList)
                                           :ColliderYobject(id,parentId,"AABB",pluginList),
                                            RenderableYobject(id,parentId,pluginList),
                                            SceneYobject(id,parentId,pluginList)
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

    pictureList = nullptr;

}

void AABBColliderYobject::registerYobject(std::shared_ptr<AABBColliderYobject> yobject)
{
    /*TODO:WORKAROUND */
    RenderableYobject::registerYobject(std::static_pointer_cast<RenderableYobject>(yobject));
    ColliderYobject::registerYobject(std::static_pointer_cast<ColliderYobject>(yobject));
    SceneYobject::registerYobject(std::static_pointer_cast<SceneYobject>(yobject));
}

void AABBColliderYobject::unregisterYobject(std::shared_ptr<AABBColliderYobject> yobject)
{
    RenderableYobject::unregisterYobject(std::static_pointer_cast<RenderableYobject>(yobject));
    ColliderYobject::unregisterYobject(std::static_pointer_cast<ColliderYobject>(yobject));
    SceneYobject::unregisterYobject(std::static_pointer_cast<SceneYobject>(yobject));
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

        /* check pixel to pixel collision*/
        if (pictureList)
        {   
            return !pictureList->isCurrentPixelTransparent(point.posX,point.posY);
        }

        return true;
    }

    return false;
    
}



bool AABBColliderYobject::collidesWith(std::shared_ptr<ColliderYobject> collider,std::string type,std::string tag)
{

    /* this collider has not the right tag*/
    if (tag != "" && tag != getTag())
        return false;
    if (type != "" && ColliderYobject::getType() != type )
        return false;


    if (!ColliderYobject::active)
    {
        return false;
    }
 
	if (collider->getType() == "AABB")
    {

        std::shared_ptr<AABBColliderYobject> targetCollider = 
            std::dynamic_pointer_cast<AABBColliderYobject>(collider);

        /*the collision detection was forced by the target. so its irrelevant
          if its active or not*/
        //if (!targetCollider->isActive())
        //    return false;

        Rectangle targetColliderRectangle = targetCollider->getRectangle();
        Rectangle sourceColliderRectangle = getRectangle();

        SDL_Rect targetSDLRect;
        SDL_Rect sourceSDLRect;

        targetSDLRect.w = targetColliderRectangle.width;
        targetSDLRect.h = targetColliderRectangle.height;
        targetSDLRect.x = targetColliderRectangle.posX;
        targetSDLRect.y = targetColliderRectangle.posY;

        sourceSDLRect.w = sourceColliderRectangle.width;
        sourceSDLRect.h = sourceColliderRectangle.height;
        sourceSDLRect.x = sourceColliderRectangle.posX;
        sourceSDLRect.y = sourceColliderRectangle.posY;

        SDL_Rect intersectionRect;

        /*check if the rects have an intersection*/
        if(SDL_IntersectRect(&sourceSDLRect,&targetSDLRect,&intersectionRect))
        {
            //std::cout << "is active"<< "\n";

            std::shared_ptr<PictureList> targetPictureList = 
                targetCollider->getPictureList();

            std::cout << "AABB Intersection: \n" 
                                      << "target: \n"
                                      <<  targetSDLRect.x <<"\n" 
                                      <<  targetSDLRect.y <<"\n"
                                      <<  targetSDLRect.w <<"\n"
                                      <<  targetSDLRect.h <<"\n"
                                      << "source: \n"
                                      <<  sourceSDLRect.x <<"\n" 
                                      <<  sourceSDLRect.y <<"\n"
                                      <<  sourceSDLRect.w <<"\n"
                                      <<  sourceSDLRect.h <<"\n"
                                      <<"intersection: \n"
                                      <<  intersectionRect.x <<"\n" 
                                      <<  intersectionRect.y <<"\n"
                                      <<  intersectionRect.w <<"\n"
                                      <<  intersectionRect.h <<"\n";

            /*check if both support picel to pixel collision, 
              i.e. they both have a picture list*/
            if (targetPictureList != nullptr && pictureList != nullptr)
            {
                //std::cout << "\nboth have a picture\n";
                for (int i = intersectionRect.x; i < intersectionRect.x + intersectionRect.w; i++)
                {
                    for (int j= intersectionRect.y; j < intersectionRect.y + intersectionRect.h; j++)
                    {
                        Position p = {i,j};

                        /*std::cout << "check pixel: " << i << "," << j 
                                  << "is point picture:" << targetCollider->isPointInCollider(p)
                                  << "," << isPointInCollider(p) <<"\n";*/
                        
                        if ( targetCollider->isPointInCollider(p) && isPointInCollider(p))
                        {
                            
                            return true;
                        }
                          
                    }
                }
                //std::cout << "\nfound no pixel\n";
                /* they support pixel to pixel collision but dont have a collision*/
                return false;
            }

            /*both not support ptp collision but have a collision*/
            if (targetPictureList == nullptr && pictureList == nullptr)
                return true;

            /* one of them have a picture. check if a pixel is in the rect of the other collider*/
            /*TODO: workaround fix this.*/
            if (targetPictureList != nullptr && pictureList == nullptr)
            {
                for (int i = intersectionRect.x; i < intersectionRect.x + intersectionRect.w; i++)
                    for (int j= intersectionRect.y; j < intersectionRect.y + intersectionRect.h; j++)
                    {
                        Position p = {i,j};
                        if (targetCollider->isPointInCollider(p))
                            return true;
                    }
            }
            if (targetPictureList == nullptr && pictureList != nullptr)
            {
                for (int i = intersectionRect.x; i < intersectionRect.x + intersectionRect.w; i++)
                    for (int j= intersectionRect.y; j < intersectionRect.y + intersectionRect.h; j++)
                    {
                        Position p = {i,j};
                        if (isPointInCollider(p))
                            return true;
                    }
            }


        }

        /*not have a collision*/
    }

    return false;
}


void AABBColliderYobject::updatePosition(int dx, int dy)
{
    posX += dx;
    posY += dy;
}

void AABBColliderYobject::setPictureList(std::shared_ptr<PictureList> pictureList)
{
    this->pictureList = pictureList;
}

std::shared_ptr<PictureList> AABBColliderYobject::getPictureList()
{
    return pictureList;
}