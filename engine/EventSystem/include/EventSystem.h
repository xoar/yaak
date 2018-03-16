#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H

#include <vector>
#include "Utils.h"
#include "GameEnginePlugin.h"
#include "GameEvents.h"
#include "PluginList.h"
#include "MainEngine.h"

#define EVENTSYSTEMNAME ("EventSystem")

class MainEngine;


class EventSystem : public GameEnginePlugin
{
    public:
        EventSystem(PluginList* pluginList);
        virtual ~EventSystem() {};

        /*get a struct with the current clicked buttons*/
        GameEvents getCurrentEvents();

        /*return the queue. this is important when you want to check if there
         were more than one event or the analyse the sequence of events*/
        std::vector <SDL_Event>* getEventQueue();
       
        /** get the new events. 
           copy them in the queue and set the gameEvents struct
        */
        void process();

        /* reset the current game event structure*/
        void resetCurrentEvents();

        virtual std::string getName() {return getPluginName();}
        static std::string getPluginName() {return EVENTSYSTEMNAME;}

    protected:

        /*analyse the event and set the flags in the game structure*/
        void analyseEvent(SDL_Event& event);

        /*the current event queue for this loop*/
        std::vector <SDL_Event>* currentEventQueue;

        /* the current game event*/
        GameEvents currentGameEvents;

        /* main engine pointer to call process event*/
        MainEngine* mainEngine;

};

#endif // EVENTSYSTEM_H
