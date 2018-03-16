#ifndef RELOADGAMEPLUGIN_H
#define RELOADGAMEPLUGIN_H

#include <vector>
#include "Utils.h"
#include "GameEnginePlugin.h"
#include "PluginList.h"
#include <exception>

#define RELOADGAMEPLUGINNAME ("ReloadGamePlugin")

class ReloadGamePlugin : public GameEnginePlugin
{
    public:
        ReloadGamePlugin(PluginList* pluginList) {reload = false;}
        virtual ~ReloadGamePlugin() {}

        bool getReloadStatus() { return reload;}
        void setReloadStatus(bool status) {reload = status;}

        virtual std::string getName() {return getPluginName();}
        static std::string getPluginName() {return RELOADGAMEPLUGINNAME;}

    protected:

        /*signal a reload*/
        bool reload;
};

/* a excpetion calss which signal a reload*/
class ReloadException: public std::exception
{
    virtual const char* what() const throw()
    {
        return "reload exception wa thrown\n";
    }
};

#endif