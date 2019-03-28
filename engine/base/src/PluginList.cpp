#include "PluginList.h"

PluginList::PluginList()
{
    //ctor
}

PluginList::~PluginList()
{
    //dtor
}


void PluginList::clear()
{

    try {

        for (auto it = plugins.begin(); it != plugins.end(); 
                 it = plugins.begin())
        {
                plugins.erase(it);
        }

            plugins.clear();
    }
    catch (std::exception& e)
    {
            std::cerr << "\n cant remove yobject " << e.what() << '\n';
            std::exit(EXIT_FAILURE);
    }

}

void PluginList::add (GameEnginePlugin* plugin)
{

    plugins[plugin->getName()] = plugin;

}

GameEnginePlugin* PluginList::get(std::string name) //throw (std::runtime_error)
{
    auto got = plugins.find (name);

    if ( got == plugins.end() )
    {
        throw std::runtime_error("PluginList: Unable to find Plugin: " + name);
    }

    return got->second;
}