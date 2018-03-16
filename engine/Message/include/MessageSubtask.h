#ifndef MESSAGENODE_H_INCLUDED
#define MESSAGENODE_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <stdexcept>
#include <string>
#include "Utils.h"
#include "Position.h"
#include "PluginList.h"
#include "Subtask.h"
#include "Message.h"
#include "Character.h"
#include "GlobalTimer.h"
#include "MessageYobject.h"
#include "TaskManager.h"
#include "GlobalSettings.h"
#include <memory>

class MessageSubtask : public Subtask
{
    public:
    MessageSubtask(PluginList* pluginList,
                   int id,
                   std::string text,
                   int characterId,
                   std::string eventName);
    
    ~MessageSubtask();

    /** show the message for the specified time. blocks  */
    virtual void process();

    Position getPosition();
    void setPosition(Position pos);
    void setPosition(int posX, int posY);

    void setTime(double time);
    void setFontPath(std::string fontPath);
    void setFontSize(int fontSize);
    void setColor(int r, int g, int b);
    void setColor(SDL_Color color);

    protected:
    std::shared_ptr<MessageYobject> messageYobject;

    /** pointer to the taskManager to pause tasks*/
    TaskManager* taskManager;

    GlobalTimer* timer;
    int elapsedTicks;
    int maxTicks;

    std::string eventName;





};

#endif // MESSAGENODE_H_INCLUDED
