#ifndef ACTIVECHARACTERLIST_H_INCLUDED
#define ACTIVECHARACTERLIST_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <stdexcept>
#include <string>
#include <vector>          // std::list
#include "Utils.h"
#include <mutex>
#include "YobjectContainer.h"
#include "PluginList.h"

#define COMPOSITORNAME ("Compositor")

class Compositor: public YobjectContainer
{
    public:

        Compositor(PluginList* pluginlist);

        /** call the render function for all object.
            assumes that the current thread have the current context,
            by a call of FinalizeContextSharing before*/
        virtual void renderYobjects();

        /** mointor functions. can be entered from one task at the same time:*/
        
        /* assign the opengl context to the current thread*/
        void lockContext();
        /* release the opengl context*/
        void freeContext();

        /* init the onpengl context. is done by the cosntructor of the compositor*/
        void initContext();

        /*have to be called before using the context with lockContext and freeContext*/
        void InitContextSharing();

        /*have to be called after using lockContext and freeContext and before renderYobjects*/
        void FinalizeContextSharing();

        /*deactivate all Yobjects in the render list*/
        void deactivateAllYobjects();

        virtual std::string getName() {return getPluginName();}
        static std::string getPluginName() {return COMPOSITORNAME;}

    protected:

        /*sort the array by increasig render priority of the object*/
        void sortByRenderPriority();


        std::mutex compositorMutex;

        SDL_Renderer *renderer;

        //context is a void pointer...
        SDL_GLContext context;
        SDL_Window* window;

};

        /* compare the objects by its render priority*/
        bool compareRenderPriority(std::shared_ptr<Yobject> yobjectLeft, 
                                   std::shared_ptr<Yobject> yobjectRight);

#endif // ACTIVECHARACTERLIST_H_INCLUDED
