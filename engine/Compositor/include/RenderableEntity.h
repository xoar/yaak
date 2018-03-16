#ifndef RENDERABLEENTITY_H
#define RENDERABLEENTITY_H

#include <RenderableYobject.h>


class RenderableEntity : public RenderableYobject
{
    public:
        RenderableEntity(int id,
                         std::string name,
                         PluginList* pluginList);

        virtual ~RenderableEntity();
        std::string getName();
    protected:
        std::string name;
    private:
};

#endif // RENDERABLEENTITY_H
