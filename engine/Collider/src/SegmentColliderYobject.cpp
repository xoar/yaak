#include "SegmentColliderYobject.h"
#include "SDL.h"

SegmentColliderYobject::SegmentColliderYobject (int id,
                                                int parentId,
                                                PluginList* pluginList)
                                                 :ColliderYobject(id,
                                                                  parentId,
                                                                  "Segment",
                                                                  pluginList),
                                                 RenderableYobject(id,
                                                                  parentId,
                                                                  pluginList)
{
    start.posX = 0;
    start.posY = 0;

    end.posX = 0;
    end.posY = 0;

    normal.dx = 0;
    normal.dy = 0;

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

void SegmentColliderYobject::registerYobject(std::shared_ptr<SegmentColliderYobject> yobject)
{
    /*TODO:WORKAROUND */
    RenderableYobject::registerYobject(std::static_pointer_cast<RenderableYobject>(yobject));
    ColliderYobject::registerYobject(std::static_pointer_cast<ColliderYobject>(yobject));
}

void SegmentColliderYobject::unregisterYobject(std::shared_ptr<SegmentColliderYobject> yobject)
{
    RenderableYobject::unregisterYobject(std::static_pointer_cast<RenderableYobject>(yobject));
    ColliderYobject::unregisterYobject(std::static_pointer_cast<ColliderYobject>(yobject));
}

SegmentColliderYobject::~SegmentColliderYobject()
{
	
}

bool SegmentColliderYobject::isPointInCollider(Position point)
{

    return false;
    
}

void SegmentColliderYobject::render()
{
    union SettingsValue debugFrames = globalSettings->getSetting("DebugFrames");
    if (debugFrames.intValue)
    {

        SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, start.posX, start.posY, end.posX, end.posY);
        /* set the color back to black*/
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    }
}

void SegmentColliderYobject::setSegment(int startX,int startY,int endX,int endY)
{
    start.posX = startX;
    start.posY = startY;

    end.posX = endX;
    end.posY = endY;

    /*right hand orientation: thumb is direction, index finger is normal*/
    /* vector (a,b) with normal (-b,a)*/
    normal.dx = - (end.posY - start.posY);
    normal.dy = (end.posX - start.posX);
}


bool SegmentColliderYobject::collidesWith(std::shared_ptr<ColliderYobject> collider,std::string type,std::string tag)
{

    /* this collider has not the right tag*/
    if (tag != "" && tag != getTag())
        return false;


    if (collider->getType() == "AABB") 
    {
        Rectangle aabb = (std::dynamic_pointer_cast<AABBColliderYobject>(collider))->getRectangle();
        return TestSegmentAABB(start,end,aabb);
    }

    return false;

}

Vector SegmentColliderYobject::getNormal()
{
    return normal;
}

/*taken from real time collision*/
// Test if segment specified by points p0 and p1 intersects AABB b
int SegmentColliderYobject::TestSegmentAABB(Point p0, Point p1, Rectangle aabb)
{

    #define EPSILON 0.0000001;

    // Box center-point
    // box is described by two points b.max and b.min
    // but a aabb has a left bottom origin and a height and width
    // Point c = (b.min + b.max) * 0.5f;
    Point c;
    c.posX = (double)aabb.posX + 0.5f*((double)aabb.width);
    c.posY = (double)aabb.posY + 0.5f*((double)aabb.height);

    // Box halflength extents
    // Vector e = b.max - c;
    Vector e;
    e.dx = (double)aabb.posX + (double)aabb.width  - c.posX;
    e.dy = (double)aabb.posY + (double)aabb.height - c.posY;

    // Segment midpoint
    //Point m = (p0 + p1) * 0.5f;
    Point m;
    m.posX = (p0.posX + p1.posX) * 0.5f;
    m.posY = (p0.posY + p1.posY) * 0.5f;

    // Segment halflength vector
    //Vector d = p1 - m;
    Vector d;
    d.dx = p1.posX - m.posX;
    d.dy = p1.posY - m.posY;
    
    // Translate box and segment to origin
    // describe the segment midpoint in the box system.
    // origin in the box system is c.
    //m = m - c;
    m.posX = m.posX - c.posX;
    m.posY = m.posY - c.posY;
    
    // Try world coordinate axes as separating axes
    double adx = abs(d.dx);
    if (abs(m.posX) > e.dx + adx) return false;
    double ady = abs(d.dy);
    if (abs(m.posY) > e.dy + ady) return false;

    // Add in an epsilon term to counteract arithmetic errors when segment is
    // (near) parallel to a coordinate axis (see text for detail)
    adx += EPSILON; ady += EPSILON;
    // Try cross products of segment direction vector with coordinate axes
    //if (abs(m.y * d.z - m.z * d.y) > e.y * adz + e.z * ady) return 0;
    //if (abs(m.z * d.x - m.x * d.z) > e.x * adz + e.z * adx) return 0;
    if (abs(m.posX * d.dy - m.posY * d.dx) > e.dx * ady + e.dy * adx) return 0;
    // No separating axis found; segment must be overlapping AABB
    return true;
}