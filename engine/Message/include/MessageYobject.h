#ifndef MESSAGEYOBJECT_H
#define MESSAGEYOBJECT_H

#include <iostream>
#include <SDL.h>

#include <stdexcept>
#include <string>
#include "Message.h"
#include "RenderableYobject.h"
#include "Character.h"
#include "GlobalSettings.h"
#include <memory>


/* NOTE: you have to call signalInitRessource or signalInitRessourceNow,
   before rendering it, or you see nothing.
   We use this approach for allowing users to change the color, font etc,
   over the getters before displaying the texture*/
class MessageYobject : public RenderableYobject
{
    public:
        MessageYobject (int id,
                        int parentId,
                        std::string text,
                        int characterId,
                        PluginList* pluginList);

        virtual ~MessageYobject();

        virtual void render();

        /*called by compositor: init/free the ressources*/
        virtual void initRessources();
        virtual void freeRessources();

        /*set a fixed text position. don't use the character's position as a offset*/
        void setFixTextPosition(bool fixedTextPosition);

        void getSize(int & width, int & height);

        Position getPosition();
        void setPosition(Position pos);
        void setPosition(int posX, int posY);

        void setFontPath(std::string fontPath);
        void setFontSize(int fontSize);
        void setColor(int r, int g, int b);
        void setColor(SDL_Color color);


    protected:

        Message* message;
        std::shared_ptr<Character> owner;
        bool fixedTextPosition;
        bool hasInitializedRessources;

    private:
};

#endif // MESSAGEYOBJECT_H
