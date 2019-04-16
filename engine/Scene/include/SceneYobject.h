#ifndef SCENEYOBJECT_H
#define SCENEYOBJECT_H

#include "Yobject.h"
#include "PluginList.h"
#include "SceneContainer.h"
#include <memory>


class SceneYobject : public Yobject
{
    public:
        SceneYobject(int id,int parentId,
                          PluginList* pluginList);

        SceneYobject(int id,
                     std::string name,
                     PluginList* pluginList);

        virtual ~SceneYobject();

        /*register/unregister this yobject in the sceneContainer*/
        virtual void registerYobject(std::shared_ptr<SceneYobject> yobject);
        virtual void unregisterYobject(std::shared_ptr<SceneYobject> yobject);

        /*attach another scene node to this to notice 
          the propagated translations. see tranlsate()*/
        void attachChild(std::shared_ptr<SceneYobject> yobject);
         /*detach a scene node from this*/
        void detachChild(std::shared_ptr<SceneYobject> yobject);

        /*propagate down the translate function*/
        virtual void translateChilds(int dx, int dy);
        /* override this function to adapt to the position diff*/
        virtual void updatePosition(int dx, int dy){}

    protected:

        SceneContainer *scene;
        std::vector<std::shared_ptr<SceneYobject>>* childs;
    private:
};

#endif // RENDERABLEYOBJECT_H
