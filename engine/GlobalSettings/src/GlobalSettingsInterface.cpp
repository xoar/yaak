#include "GlobalSettingsInterface.h"
#include "GlobalSettings.h"
#include "PluginList.h"

void registerSetting(void* pluginList,const char* specifier, union SettingsValue value)
{
    GlobalSettings* globSet = (GlobalSettings*) ((PluginList*) pluginList)->get( GlobalSettings::getPluginName());
    globSet->registerSetting(std::string(specifier),value);

}

union SettingsValue getSetting(void* pluginList,const char* specifier)
{
    GlobalSettings* globSet = (GlobalSettings*) ((PluginList*) pluginList)->get( GlobalSettings::getPluginName());
    return globSet->getSetting(std::string(specifier));

}