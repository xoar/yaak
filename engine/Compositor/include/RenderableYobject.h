#ifndef RENDERABLEYOBJECT_H
#define RENDERABLEYOBJECT_H

#include "Yobject.h"
#include "PluginList.h"
#include "Compositor.h"
#include <memory>

class Compositor;

class RenderableYobject : public Yobject
{
    public:
        RenderableYobject(int id,int parentId,
                          PluginList* pluginList);

        virtual ~RenderableYobject();
        virtual void render() {};

        /*called by logic: register/unregister the yobject in the render queue*/
        /*NOTE: not init the ressources.*/
        virtual void registerYobject(std::shared_ptr<RenderableYobject> yobject);
        virtual void unregisterYobject(std::shared_ptr<RenderableYobject> yobject);


        /** signals if the yobject will be rendered. 
            yobjects are active by default*/
        void activate();
        void deactivate();

        /** returns if it should be rendered*/
        bool isActive();

        /*called by logic: init/free the ressource now, by getting the gl context*/
        /*TODO: renaming, shold be signalInitRessource, because the queded method was deleted*/
        void signalInitRessourcesNow();
        void signalFreeRessourcesNow();

        /*called by compositor: init/free the ressources*/
        virtual void initRessources() {};
        virtual void freeRessources() {};

    protected:
        SDL_Renderer    *renderer;
        Compositor *compositor;

        /* flags which indicate if it will be rendered or not*/
        bool active;

    private:
};

#endif // RENDERABLEYOBJECT_H
