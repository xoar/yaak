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

        virtual ~SceneYobject();

        virtual void registerYobject(std::shared_ptr<SceneYobject> yobject);
        virtual void unregisterYobject(std::shared_ptr<SceneYobject> yobject);

    protected:
        SceneContainer *scene;

    private:
};

#endif // RENDERABLEYOBJECT_H
