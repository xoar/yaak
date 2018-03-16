#include "Utils.h"

/** loads a text with the ttf extension */
SDL_Texture* loadText(std::string message, std::string fontFile,SDL_Color color, int fontSize,SDL_Renderer *ren)
{
    //Open the font
    TTF_Font *font = nullptr;
    font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr)
    throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());
    //set a outline
    //TTF_SetFontOutline(font,1);
    //Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surf);
    //Clean up unneeded stuff
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);

    return texture;
}

/** loads a text with the ttf extension */
SDL_Texture* loadTextOutline(std::string message, std::string fontFile,SDL_Color color, int fontSize,int outline,SDL_Renderer *ren)
{
    //Open the font
    TTF_Font *font = nullptr;
    font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr)
    throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());
    //set a outline
    TTF_SetFontOutline(font,outline);
    //Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surf);
    //Clean up unneeded stuff
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);

    return texture;
}

/** loads an image with the image extention library */
SDL_Texture* LoadImage(std::string file,SDL_Renderer *renderer)
{
    SDL_Texture* tex = nullptr;
    tex = IMG_LoadTexture(renderer, file.c_str());
    if (tex == nullptr)
        throw std::runtime_error("Failed to load image: " + file + IMG_GetError());
    return tex;
}

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message too
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/

void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}


/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw too
* @param x The x coordinate to draw too
* @param y The y coordinate to draw too
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}
