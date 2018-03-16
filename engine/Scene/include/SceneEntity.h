#ifndef SCENEENTITY_H
#define SCENEENTITY_H

#include <SceneYobject.h>


class SceneEntity : public SceneYobject
{
    public:
        SceneEntity(int id,
                    std::string name,
                    PluginList* pluginList);

        virtual ~SceneEntity();
        virtual std::string getName();
    protected:
        std::string name;
    private:
};

#endif // SCENEENTITY_H