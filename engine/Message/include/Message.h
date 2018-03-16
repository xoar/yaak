#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <SDL.h>

#include <stdexcept>
#include <string>

#include "Utils.h"
#include "Position.h"

class Message
{
    public:
        Message(std::string text,std::string fileName,
                int px , int py,
                int fontSize,
                SDL_Color color,
                SDL_Renderer *renderer);

        virtual ~Message();

        void getSize(int & width, int & height);
        Position getPosition();
        void setPosition(Position pos);
        void setPosition(int posX, int posY);
        void setTime(double time);
        void setFontPath(std::string fileName);
        void setFontSize(int fontSize);
        void setColor(int r, int g, int b);
        void setColor(SDL_Color color);
        
        void destroyTexture();
        void createTexture();
        void render();

    protected:
        int posX;
        int posY;
        //height and width of the texture rectangle*/
        int width;
        int height;

        int fontSize;
        std::string fileName;
        SDL_Texture     *texture;
        SDL_Texture     *outline;
        SDL_Renderer    *renderer;
        SDL_Color        color;
        std::string      text;

    private:
};

#endif // MESSAGE_H
