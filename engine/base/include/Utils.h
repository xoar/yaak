#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdexcept>
#include <string>


SDL_Texture* loadText(std::string message, std::string fontFile,SDL_Color color, int fontSize,SDL_Renderer *ren);
SDL_Texture* loadTextOutline(std::string message, std::string fontFile,SDL_Color color, int fontSize,int outline,SDL_Renderer *ren);

SDL_Texture* LoadImage(std::string file,SDL_Renderer *renderer);

void logSDLError(std::ostream &os, const std::string &msg);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

SDL_Surface* LoadSurface(std::string file);

#endif // UTILS_H_INCLUDED
