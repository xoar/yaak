#ifndef PICTURE_H
#define PICTURE_H

#include <iostream>
#include <SDL.h>

#include <stdexcept>
#include <string>

#include "Utils.h"
#include "Position.h"
#include "Rectangle.h"
#include "Size.h"

class Picture
{
    public:
        Picture(std::string fileName, int px , int py, SDL_Renderer *renderer);
        virtual ~Picture();
        Position getPosition();
        void setPosition(Position pos);
        void setPosition(int posX, int posY);
        Size getSize();
        void render();
    protected:
        int posX;
        int posY;

        int width;
        int height;
        
        SDL_Texture     *texture;
        SDL_Renderer    *renderer;

    private:
};

#endif // PICTURE_H
