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
    if (x > width || y > height || y < 0 || x <0)
        return true;


//-------------------------------------
    /*TODO: workaround: we need to load surfaces intead textures to support the 
      target memory layout.
      then we could use https://lazyfoo.net/tutorials/SDL/40_texture_manipulation/index.php
    
    TODO: with this method we still have to assure that the format is supported: see SDL_GetRendererInfo   
    possible another approach ? https://gamedev.stackexchange.com/questions/62705/how-do-i-access-the-pixels-of-an-sdl-2-texture

    */

    //SDL_Rect    rect;
    //use argb with 32 bit and 4 bytes per pixel
    /*Uint32      format  = SDL_PIXELFORMAT_ARGB2101010;
    void*       pixels;
    int         pitch   = 8;


    SDL_SetRenderTarget(renderer,texture);


    if (SDL_RenderReadPixels(renderer,NULL, format,&pixels,pitch) != 0)
    {
        printf( "Unable to acces texture! %s\n", SDL_GetError() );
        return false;

    }

    int bpp = SDL_BYTESPERPIXEL(format);
    
    //SDL_PixelFormat* pixel_format =  SDL_AllocFormat(format);


    Uint8* p = (Uint8*)pixels + y *pitch + x * bpp;
    Uint32 pixelColor;
     
    pixelColor = *(Uint32*)p;


    std::cout << "pixel: "<< pixelColor <<"\n";

    //Uint8 red, green, blue, alpha;
    //SDL_GetRGBA(pixelColor,pixel_format, &red, &green, &blue, &alpha);
 
    //SDL_FreeFormat(pixel_format);*/


//--------------------------------------
    /*void*       pixels;
    int         pitch;*/

    /*if( SDL_LockTexture( texture, NULL, &pixels, &pitch ) != 0 )
    {
            printf( "Unable to lock texture! %s\n", SDL_GetError() );
            return false;
    }*/
    /*
    SDL_PixelFormat* pixel_format =  SDL_AllocFormat(SDL_PIXELFORMAT_UNKNOWN);

    std::cout << "format: " << SDL_GetPixelFormatName(pixel_format->format) << "\n";
    std::cout << "bit per pixel : " << pixel_format->BitsPerPixel << "\n";
    std::cout << "bytes per pixel: " << pixel_format->BytesPerPixel << "\n";

    int bpp = pixel_format->BytesPerPixel;

    Uint8* p = (Uint8*)pixels + y *pitch + x * bpp;
    Uint32 pixelColor = *(Uint32*)p;*/

//----------------------------------------


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

    return alpha > 0;
}