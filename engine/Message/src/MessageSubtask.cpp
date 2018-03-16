#include "MessageSubtask.h"
#include <stdexcept>

MessageSubtask::MessageSubtask(PluginList* pluginList,
                        int id,
                        std::string text,
                        int characterId,
                        std::string eventName)
                        : Subtask(id)
{

    elapsedTicks = 0;
    this->eventName = eventName;
    
    GlobalSettings* globalSettings = nullptr;
    try 
    { 
        /*get the default time and configure the maxticks with it*/
        globalSettings = (GlobalSettings*) pluginList->get(GlobalSettings::getPluginName());
    }
    catch(std::runtime_error& e)
    {
        std::cerr <<"ERROR: Cant find the global Settings, subtask id: "<< id 
        << ", "  << e.what() <<" \n";
    }

    union SettingsValue defaultTime = globalSettings->getSetting("DefaultTime");
    /*set the max ticks*/
    this->setTime(defaultTime.doubleValue);

    /*build the message yobject*/
    messageYobject = std::make_shared<MessageYobject>(0,id,text,characterId,pluginList);
    messageYobject->registerYobject(messageYobject);


    /*try to assign the global timer */
    try 
    { 
        this->timer = (GlobalTimer*) pluginList->get(GlobalTimer::getPluginName()); 
    }
    catch(std::runtime_error& e)
    {
    /* for some reasons, the message node cant access the global timer */
        std::cerr <<"ERROR: Cant find the global timer, subtask id: "<< id 
        << ", "  << e.what() <<" \n";
    }

    try 
    { 
        this->taskManager = ((TaskManager*) pluginList->get(TaskManager::getPluginName()));
    }
    catch(std::runtime_error& e)
    {
    /* for some reasons, the message node cant access the task manager */
        std::cerr <<"ERROR: Cant find the task manager, subtask id: "<< id 
        << ", "  << e.what() <<" \n";
    }

}
MessageSubtask::~MessageSubtask()
{
    messageYobject->unregisterYobject(messageYobject);
    messageYobject.reset();
}

/** this is the process function which must be overriden
    to implement the disired functionality */
void MessageSubtask::process()
{

    /*build the texture*/
    messageYobject->signalInitRessourcesNow();
    /*just to be sure its active*/
    messageYobject->activate();

    while(elapsedTicks <= maxTicks)
    {

        elapsedTicks += timer->getTicksForCurrentFrame();
        //std::cout << "Subtask: " << id  <<" elapsed time: " << elapsedTicks  <<std::endl;

        taskManager->suspendTaskUntilNextRound(eventName);

    }

    //std::cout <<"Deactivate Message Subtask: " << id <<std::endl;

    messageYobject->deactivate();

    elapsedTicks = 0;

}


void MessageSubtask::setTime(double time)
{
    this->maxTicks = time*1000;
}

void MessageSubtask::setPosition(Position pos)
{
    this->messageYobject->setPosition(pos);
}

void MessageSubtask::setPosition(int posX, int posY)
{
    this->messageYobject->setPosition(posX, posY);
}

Position MessageSubtask::getPosition()
{
    return this->messageYobject->getPosition();
}

void MessageSubtask::setFontPath(std::string fontPath)
{
    this->messageYobject->setFontPath(fontPath);
}

void MessageSubtask::setFontSize(int fontSize)
{
    this->messageYobject->setFontSize(fontSize);
}

void MessageSubtask::setColor(int r, int g, int b)
{
    this->messageYobject->setColor(r,g,b);
}

void MessageSubtask::setColor(SDL_Color color)
{
    this->messageYobject->setColor(color);
}
