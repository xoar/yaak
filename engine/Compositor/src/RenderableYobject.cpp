#include "RenderableYobject.h"
#include "MainEngine.h"

RenderableYobject::RenderableYobject(int id,
                                     int parentId,
                                     PluginList* pluginList)
                                     : Yobject(id,parentId)
{



    /*try to get the renderer*/
    MainEngine* rendererPlugin = (MainEngine*) pluginList->get(MainEngine::getPluginName());
    if (rendererPlugin  == nullptr)
    {
        std::cerr << "ERROR: Cant find the renderer plugin,"
        << "needed for the rendeable yobject with id:"
        << id << "\n";
    }

    this->renderer = rendererPlugin->getRenderer();
    if (this->renderer  == nullptr)
    {
        std::cerr << "ERROR: Cant get the renderer from plugin,"
        << "needed for the rendeable yobject with id:"
        << id << "\n";
    }


    /*try to assign the compositor*/
    this->compositor = (Compositor*) pluginList->get(Compositor::getPluginName());

    if (this->compositor  == nullptr)
    {
    /* for some reasons, the list doesnt have the compositor */
        std::cerr << "ERROR: Cant find the compositor,"
        << "needed for the rendeable yobject with id:"
        << id << "\n";
    }

     /* active by default*/
    active = true;

    /*set the default priority*/
    renderPriority = 0;

}


RenderableYobject::RenderableYobject(int id,
                                   std::string name,
                                   PluginList* pluginList)
                                   : RenderableYobject(id,0,pluginList)
{
    this->name = name;
    this->type = "Entity";
}


RenderableYobject::~RenderableYobject()
{
}


void RenderableYobject::registerYobject(std::shared_ptr<RenderableYobject> yobject)
{
    compositor->addYobject(yobject);
}


void RenderableYobject::unregisterYobject(std::shared_ptr<RenderableYobject> yobject)
{
    compositor->removeYobject(yobject);
}

void RenderableYobject::signalInitRessourcesNow()
{
    compositor->lockContext();
    initRessources();
    compositor->freeContext();
}

void RenderableYobject::signalFreeRessourcesNow()
{
    compositor->lockContext();
    freeRessources();
    compositor->freeContext();
}

void RenderableYobject::activate()
{
     active = true;
}

void RenderableYobject::deactivate()
{
    active = false;
}

 bool RenderableYobject::isActive()
 {
    return active;
 }

void RenderableYobject::setRenderPriority(double priority)
{
    renderPriority = priority;
}

double RenderableYobject::getRenderPriority()
{
    return renderPriority;
}