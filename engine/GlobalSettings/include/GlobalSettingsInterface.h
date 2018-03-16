#ifndef GLOBALSETTINGSINTERFACE_H
#define GLOBALSETTINGSINTERFACE_H

#include "SettingsValue.h"

#ifdef __cplusplus
extern "C" 
{
#endif

/** register a settings value under a given specifier.*/
void registerSetting(void* pluginList,const char* specifier, union SettingsValue value);


/** try to get a value registered under a specific specifier;
* returns the value or throw an exception*/
union SettingsValue getSetting(void* pluginList,const char* specifier);


#ifdef __cplusplus
}
#endif

#endif