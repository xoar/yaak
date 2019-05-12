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

        /* assure that you have lock the compositor before using this function*/
        bool isPixelTransparent(int px, int py);
        Size getSize();
        void render();
    protected:
        int posX;
        int posY;

        int width;
        int height;
        
        SDL_Texture     *texture;
        SDL_Renderer    *renderer;

        SDL_Surface *surface;

        std::string fileName;

    private:
};

#endif // PICTURE_H
