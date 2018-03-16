#include "MessageYobjectInterface.h"
#include "MessageYobject.h"
#include <memory>

/*define the struct. Just a wrapper for the cpp object*/
struct MessageYobjectStruct{
    std::shared_ptr<MessageYobject> message;
};

MessageYobjectStructPtr MessageYobjectConstructor(int id,
                                                  int parentId,
                                                  const char* text,
                                                  int characterId,
                                                  void* pluginList)
{
    MessageYobjectStructPtr message  =  new MessageYobjectStruct();

    message->message = std::make_shared<MessageYobject>(id,
                                                        parentId,
                                                        std::string(text),
                                                        characterId,
                                                        (PluginList*) pluginList
                                                        );
    message->message->registerYobject(message->message);

    return message;

}

/** the the active status. active by default*/
void MessageYobjectActivate(MessageYobjectStructPtr message)
{
    message->message->activate();
}

void MessageYobjectDeactivate(MessageYobjectStructPtr message)
{
   message->message->deactivate();
}

void MessageYobjectGetSize(MessageYobjectStructPtr message,
                           int* width, int* height)
{
     message->message->getSize(*width,*height);
}

void MessageYobjectDestructor(MessageYobjectStructPtr message)
{
    message->message->unregisterYobject(message->message);
    message->message.reset();
    free(message);
}

void MessageYobjectFreePointerStruct(MessageYobjectStructPtr message)
{
    message->message.reset();
    free(message);
}

Position MessageYobjectGetPosition(MessageYobjectStructPtr message)
{
     return message->message->getPosition();
}

void MessageYobjectSetPosition(MessageYobjectStructPtr message,Position pos)
{
     message->message->setPosition(pos);
}

void MessageYobjectSetPosition2I(MessageYobjectStructPtr message,int posX, int posY)
{
     message->message->setPosition(posX,posY);
}

void MessageYobjectSignalInitRessources(MessageYobjectStructPtr message)
{
     message->message->signalInitRessourcesNow();
}

void MessageYobjectSetColor3I(MessageYobjectStructPtr message,int r, int g, int b)
{
     message->message->setColor(r,g,b);
}

void MessageYobjectSetColor(MessageYobjectStructPtr message,Color pcolor)
{

    SDL_Color sdlColor;
    sdlColor.r = pcolor.r;
    sdlColor.g = pcolor.g;
    sdlColor.b = pcolor.b;

    message->message->setColor(sdlColor);
}

void MessageYobjectSetFontSize(MessageYobjectStructPtr message,int fontSize)
{
     message->message->setFontSize(fontSize);
}