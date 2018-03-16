#ifndef TRIGGERZONEPLUGIN_H
#define TRIGGERZONEPLUGIN_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>          // std::list
#include "Utils.h"
#include "YobjectContainer.h"

#define TRIGGERZONEPLUGINNAME ("TriggerZonePlugin")


class TriggerZonePlugin: public YobjectContainer
{
public:
    virtual std::string getName() {return getPluginName();}
    static std::string getPluginName() {return TRIGGERZONEPLUGINNAME;}
};

#endif // TRIGGERZONEPLUGIN_H
