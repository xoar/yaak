#ifndef INITGLOBALS_H
#define INITGLOBALS_H

#include "PluginUtils.h"
#include "TestPlugin.h"


void InitGlobals()
{

    union SettingsValue defaultColor;
    /* actual the parser cant support a statement 
       like defaultColor.colorValue =  { 0, 0, 0 }; Is it C99?*/
    Color defaultColorValue = { 0, 0, 0 };
    defaultColor.colorValue =  defaultColorValue;
    registerSetting(pluginList,"DefaultColor", defaultColor);


    union SettingsValue defaultFont;
    defaultFont.stringValue = "../res/SourceSansPro-Regular.ttf";
    registerSetting(pluginList,"DefaultFont", defaultFont);

    union SettingsValue defaultPos;
    Position defaultPositionValue = {10,20 };
    defaultPos.positionValue = defaultPositionValue;
    registerSetting(pluginList,"DefaultPosition", defaultPos);

    union SettingsValue defaultSize;
    defaultSize.intValue = 30;
    registerSetting(pluginList,"DefaultSize", defaultSize);

    union SettingsValue defaultTime;
    defaultTime.doubleValue = 10.5;
    registerSetting(pluginList,"DefaultTime", defaultTime);

    union SettingsValue debugFrames;
    debugFrames.intValue = 1;
    registerSetting(pluginList,"DebugFrames", debugFrames);


}

#endif

