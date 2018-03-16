#ifndef GLOBALSTTINGS_H
#define GLOBALSTTINGS_H

#include "Utils.h"
#include "GameEnginePlugin.h"
#include <unordered_map>

#include "SettingsValue.h"

#define GLOBALSETTINGSNAME ("GlobalSettings")

/* since we have no dynamic typing we can use serialization or unions or some 
   polymorpic stuff to store several different objects in a hash map.
   i use unions*/


class GlobalSettings : public GameEnginePlugin
{
    public:
        

        GlobalSettings();
        virtual ~GlobalSettings();

        /** register a settings value under a given specifier.
            overwrites it when the specifier was already in use*/
        void registerSetting(std::string specifier, SettingsValue value);


        /** try to get a value registered under a specific specifier;
        * returns the value or throw an exception*/
        SettingsValue getSetting(std::string specifier);

        virtual std::string getName() {return getPluginName();}
        static std::string getPluginName() {return GLOBALSETTINGSNAME;}
    
    protected:
        std::unordered_map<std::string,SettingsValue>* settingsList;

};



#endif
