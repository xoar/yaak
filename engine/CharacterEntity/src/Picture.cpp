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

    this->fileName = fileName;

    try
    {
        surface = LoadSurface(fileName);
    } catch (const std::runtime_error &e){
        std::cout << "Loading picture: " << fileName
                  << "failed: " << e.what() << std::endl;
    }
    
}


Picture::~Picture()
{

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

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

/*code taken from : http://www.sdltutorials.com/sdl-per-pixel-collision*/
/*and https://stackoverflow.com/questions/19107476/get-pixel-info-from-sdl2-texture*/
/* assure that you have lock the compositor before using this function*/
bool Picture::isPixelTransparent(int px, int py)
{

    /* transfomr the coords to local coords*/
    int x = px - posX;
    int y = py - posY;


    /* if the pixel coord is outside the image*/
    if (x >= width || y >= height || y < 0 || x <0)
        return true;

    if (!surface)
    {
        std::cerr << "Picture not loaded a surface\n";
        std::exit(1);
    }


    int bpp = surface->format->BytesPerPixel;
    Uint8* p = (Uint8*)surface->pixels + y *surface->pitch + x * bpp;
    Uint32 pixelColor;
     
    switch(bpp)
    {
        case(1):
            pixelColor = *p;
            break;
        case(2):
            pixelColor = *(Uint16*)p;
            break;
        case(3):
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                pixelColor = p[0] << 16 | p[1] << 8 | p[2];
            else
                pixelColor = p[0] | p[1] << 8 | p[2] << 16;
            break;
        case(4):
            pixelColor = *(Uint32*)p;
            break;
    }
     
    Uint8 red, green, blue, alpha;
    SDL_GetRGBA(pixelColor, surface->format, &red, &green, &blue, &alpha);
 
    //int alpha = 1;

    /*if (alpha == 0) 
        std::cout << "transparent\n";
    else
        std::cout << "not transparent\n";*/

    return alpha == 0;
}