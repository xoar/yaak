#include "Picture.h"

Picture::Picture(std::string fileName, int px , int py, SDL_Renderer *renderer)
{
    posX = px;
    posY = py;
    this->renderer = renderer;

    try
    {
        texture = LoadImage(fileName,renderer);
    } catch (const std::runtime_error &e){
        std::cout << "Loading picture: " << fileName
                  << "failed: " << e.what() << std::endl;
    }

    //get the width and height of the image
    if (SDL_QueryTexture(texture, NULL, NULL, &width, &height))
    {
        std::cout <<  "Getting picture size of: " << fileName
                  <<  "failed: " << SDL_GetError() << std::endl;
    }
}


Picture::~Picture()
{

    SDL_DestroyTexture(texture);

}

Size Picture::getSize()
{
    Size size;
    size.width = width;
    size.height = height;

    return size;
}


void Picture::render()
{
    renderTexture(texture,renderer, posX, posY);
}

void Picture::setPosition(Position pos)
{
    this->posX = pos.posX;
    this->posY = pos.posY;
}

void Picture::setPosition(int posX, int posY)
{
    this->posX = posX;
    this->posY = posY;
}

Position Picture::getPosition()
{
    Position pos;
    pos.posX = this->posX;
    pos.posY = this->posY;
    return pos;
}
