#include "EventSystem.h"

EventSystem::EventSystem(PluginList* pluginList)
{
    currentEventQueue = new std::vector <SDL_Event>();

    resetCurrentEvents();

    mainEngine = (MainEngine*) pluginList->get( MainEngine::getPluginName());

    currentGameEvents.mouseX = -1;
    currentGameEvents.mouseY = -1;
}

GameEvents EventSystem::getCurrentEvents()
{

    return currentGameEvents;

}

void EventSystem::resetCurrentEvents()
{
    currentGameEvents.leftMouseButtonPressed = 0;
    currentGameEvents.rightMouseButtonPressed = 0;
    currentGameEvents.mouseMoved = 0;
}

/*analyse the event and set the flags in the game structure*/
/* also forward them to the system to let the system decide if it wants to quit*/
void EventSystem::analyseEvent(SDL_Event& event)
{

    /* let the system decide if it wants to quit*/
    mainEngine->processEvent(event);

    switch (event.type)
    {

        case SDL_MOUSEMOTION:
            currentGameEvents.mouseMoved = 1;
            currentGameEvents.mouseX = event.motion.x;
            currentGameEvents.mouseY = event.motion.y;
            break;

        case SDL_MOUSEBUTTONUP:

            currentGameEvents.mouseX = event.button.x;
            currentGameEvents.mouseY = event.button.y;

            if (event.button.button ==  SDL_BUTTON_LEFT)
            {
                currentGameEvents.leftMouseButtonPressed = 1;

                std::cout << "EventSys: left button pressed \n";
                std::cout << "EventSys: at position" 
                          << currentGameEvents.mouseX << ", "  
                          << currentGameEvents.mouseY << "\n";
            }
            if (event.button.button ==  SDL_BUTTON_RIGHT)
            {
                currentGameEvents.rightMouseButtonPressed = 1;

                std::cout << "EventSys: right button pressed \n";
                std::cout << "EventSys: at position" 
                          << currentGameEvents.mouseX << ", "  
                          << currentGameEvents.mouseY << "\n";
            }

            //std::cout << "bitmask: " << event.button.button << "\n";
                
            break;
    }

}

void EventSystem::process()
{
    SDL_Event event;

    /* reset the game event struct + queue*/
    resetCurrentEvents();
    currentEventQueue->clear();


    while (SDL_PollEvent(&event)){

        /*copy the event in the queue*/
        currentEventQueue->push_back(event);

        /* set the game event struct attributes and forward them to the engine*/
        analyseEvent(event);
    }
}

std::vector <SDL_Event>* EventSystem::getEventQueue()
{
    return currentEventQueue;
}
