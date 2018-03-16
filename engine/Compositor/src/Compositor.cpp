#include "Compositor.h"
/*to avoid include problems we include them herer*/
#include "RenderableEntity.h"
#include "RenderableYobject.h"
#include "MainEngine.h"
Compositor::Compositor(PluginList* pluginlist) : YobjectContainer()
{

    this->renderer = ((MainEngine*) pluginlist->get( MainEngine::getPluginName() ))->getRenderer();
    this->window = ((MainEngine*) pluginlist->get( MainEngine::getPluginName() ))->getWindow();
    
    initContext();
}


void Compositor::renderYobjects()
{
    /* normally there should be no logic element block this... but
       to ensure it ... */

    /*it is guaranteed through FinalizeContextSharing, that we have a valid context*/
    compositorMutex.lock();


    /* clear the screen */
    SDL_RenderClear(renderer);

    /* render the objetcs */
    for (auto it = yobjectList->begin();it != yobjectList->end(); it++)
    {
        /*std::weak_ptr<Yobject> yobject = (*it);
        std::weak_ptr<RenderableYobject> ryobject = std::static_pointer_cast<RenderableYobject>(yobject);
        if ( ryobject->isActive()) ryobject->render();*/
        RenderableYobject* yobject = (RenderableYobject*) (*it).get();
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
            /*std::weak_ptr<Yobject> yobject = (*it);
            std::weak_ptr<RenderableYobject> ryobject = std::static_pointer_cast<RenderableYobject>(yobject);
            ryobject->deactivate();*/
            RenderableYobject* yobject = (RenderableYobject*) (*it).get();
            yobject->deactivate();
    }
}