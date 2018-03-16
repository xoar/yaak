#ifndef SCENECONTAINER_H
#define SCENECONTAINER_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Utils.h"
#include "YobjectContainer.h"

#define SCENECONTAINERNAME ("SceneContainer")


class SceneContainer: public YobjectContainer
{
    public:
        virtual std::string getName() {return getPluginName();}
        static std::string getPluginName() {return SCENECONTAINERNAME;}
};

#endif