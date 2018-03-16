#include "GlobalSettings.h"

GlobalSettings::GlobalSettings()
{
    settingsList = new std::unordered_map<std::string,SettingsValue>();
}


GlobalSettings::~GlobalSettings()
{

    /* clear all elemtents */
    settingsList->clear();

    /*delete the list*/
    delete settingsList;
}


void GlobalSettings::registerSetting(std::string specifier, SettingsValue value)
{
    (*settingsList) [ specifier ] = value;

}


SettingsValue GlobalSettings::getSetting(std::string specifier)
{
    /*find the specifier in the list*/

    /* test if the specifier is in the list*/
    SettingsValue empty;

    auto settingsIt = settingsList->find (specifier);

    /* found it?*/
    if ( settingsIt != settingsList->end() )
    {
        return settingsIt->second;
    }

    /** TODO: throw an exception*/

    return empty;

}