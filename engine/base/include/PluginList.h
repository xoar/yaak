#ifndef PLUGINLIST_H
#define PLUGINLIST_H

#include <string>
#include <unordered_map>
#include <stdexcept>

#include "GameEnginePlugin.h"

class PluginList
{
    public:
        PluginList();
        virtual ~PluginList();
        void add (GameEnginePlugin* plugin);

        GameEnginePlugin* get(std::string name) throw (std::runtime_error);
    protected:
        std::unordered_map<std::string, GameEnginePlugin*> plugins;
};

#endif // PLUGINLIST_H
