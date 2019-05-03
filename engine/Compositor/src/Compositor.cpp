#include "Compositor.h"
/*to avoid include problems we include them herer*/
#include "RenderableYobject.h"
#include "MainEngine.h"
#include  <algorithm>
Compositor::Compositor(PluginList* pluginlist) : YobjectContainer()
{

    this->renderer = ((MainEngine*) pluginlist->get( MainEngine::getPluginName() ))->getRenderer();
    this->window = ((MainEngine*) pluginlist->get( MainEngine::getPluginName() ))->getWindow();
    
    initContext();

    windowHeight = 768;
    windowWidth =  1024;
}


void Compositor::renderYobjects()
{
    /* normally there should be no logic element block this... but
       to ensure it ... */

    /*it is guaranteed through FinalizeContextSharing, that we have a valid context*/
    compositorMutex.lock();

    /*sort the queue to reflect players which move up the screen and now hide new things*/
    sortByRenderPriority();

    /* clear the screen */
    SDL_RenderClear(renderer);

    /* render the objetcs */
    for (auto it = yobjectList->begin();it != yobjectList->end(); it++)
    {
        std::shared_ptr<RenderableYobject> yobject = 
            std::static_pointer_cast<RenderableYobject>(*it);

        if ( yobject->isActive()) yobject->render();
    }

    /* after the render routine of every object was called
     * apply the rendering to screen
     */

    SDL_RenderPresent(renderer);


    /** unlock the mutex. dont free the context, needed for the swapping*/
    compositorMutex.unlock();
}

void Compositor::InitContextSharing()
{
    //detach the context without locking*/
    if (SDL_GL_MakeCurrent(NULL,NULL))
    {
        std::cout <<  "Init Context Sharing failed: " 
                  <<  SDL_GetError() << std::endl;

    }

}


void Compositor::FinalizeContextSharing()
{
    /*get the current context without locking
      needed by the renderYobjects and ohter intern sdl calls like swapBuffers*/
    if (SDL_GL_MakeCurrent(window,context))
    {
        std::cout <<  "FinalizeContextSharing failed: " 
                  <<  SDL_GetError() << std::endl;
    }
}

void Compositor::lockContext()
{
    if (context)
    {
        compositorMutex.lock();
        if (SDL_GL_MakeCurrent(window,context))
        {
            std::cout <<  "Activating context failed: " 
                      <<  SDL_GetError() << std::endl;
        }
    }
        
}

void Compositor::freeContext()
{
    if (context)
    {
        if (SDL_GL_MakeCurrent(NULL,NULL))
        {
            std::cout <<  "Deactivating context failed: " 
                      <<  SDL_GetError() << std::endl;

        }
        compositorMutex.unlock();
    }
        
}

void Compositor::initContext()
{
    /* get the current context.*/
    context = SDL_GL_GetCurrentContext();
}

void Compositor::deactivateAllYobjects()
{
    /*nobody should change the list while iterating*/
    std::lock_guard<std::recursive_mutex> lock(containerMutex);
        
    for (auto it = yobjectList->begin();it != yobjectList->end(); it++)
    {   
            std::shared_ptr<RenderableYobject> yobject = 
                std::static_pointer_cast<RenderableYobject>(*it);
            yobject->deactivate();
    }
}

/* compare the objects by its render priority*/
bool compareRenderPriority(std::shared_ptr<Yobject> yobjectLeft , 
                           std::shared_ptr<Yobject> yobjectRight)
{
    std::shared_ptr<RenderableYobject> left =
        std::static_pointer_cast<RenderableYobject>(yobjectLeft);
    
    std::shared_ptr<RenderableYobject> right =
            std::static_pointer_cast<RenderableYobject>(yobjectRight);

    return (left->getRenderPriority() < right->getRenderPriority());
}

/*sort the array by render priority of the object*/
void Compositor::sortByRenderPriority()
{
    // sort by increaing priority 
    std::sort(yobjectList->begin(), yobjectList->end(), compareRenderPriority);
}


/*set the windows logical size to calculate the display scale*/
void Compositor::setWindowSize(int height, int width)
{
    windowWidth = width;
    windowHeight = height;
}

double Compositor::getDisplayScaleWidth()
{
    return windowWidth;
}

double Compositor::getDisplayScaleHeight()
{
    return windowHeight;
}