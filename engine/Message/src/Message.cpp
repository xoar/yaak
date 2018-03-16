#include "Message.h"

Message::Message(std::string text,std::string fileName,
                int px , int py,
                int fontSize,
                SDL_Color color, SDL_Renderer *renderer)
{
    posX = px;
    posY = py;

    height = -1;
    width = -1;

    this->fontSize = fontSize;
    this->renderer = renderer;
    this->color = color;
    this->text = text;
    this->fileName = fileName;
    this->texture = nullptr;
    this->outline = nullptr;
}

Message::~Message()
{
    if (texture)
        std::cout << "ERROR: message texture should be destoryed";
}

void Message::render()
{
    if (outline)
        renderTexture(outline,renderer, posX, posY);

    if (texture)
        renderTexture(texture,renderer, posX, posY);
}

void Message::setPosition(Position pos)
{
    this->posX = pos.posX;
    this->posY = pos.posY;
}

void Message::setPosition(int posX, int posY)
{
    this->posX = posX;
    this->posY = posY;
}

Position Message::getPosition()
{
    Position pos;
    pos.posX = this->posX;
    pos.posY = this->posY;
    return pos;
}

void Message::getSize(int & width, int & height)
{
    
    if (texture)
    {
        width = this->width;
        height = this->height;
    }
    else
    {
        width = -1;
        height -1;
    }
}

void Message::setFontPath(std::string fileName)
{
    this->fileName = fileName;
}

void Message::setFontSize(int fontSize)
{
    this->fontSize = fontSize;
}

void Message::setColor(int r, int g, int b)
{

    SDL_Color color;
    color.r = r;
    color.g = g;
    color.b = b;

    this->color = color;
}

void Message::setColor(SDL_Color color)
{
    this->color = color;
}

void Message::createTexture()
{
    if (texture)
        SDL_DestroyTexture(texture);
    if (outline)
        SDL_DestroyTexture(outline);

    this->texture = loadText(text,fileName,color,fontSize,renderer);
    this->outline = loadTextOutline(text,fileName,{0,0,0},fontSize,1,renderer);

    //get the width and height of the image
    if (SDL_QueryTexture(texture, NULL, NULL, &width, &height))
    {
        std::cout <<  "Getting text size of: " << fileName
                  <<  "failed: " << SDL_GetError() << std::endl;
    }
}

void Message::destroyTexture()
{
   if (texture)
        SDL_DestroyTexture(texture);
    if (outline)
        SDL_DestroyTexture(outline);
    
    texture = nullptr;
}
