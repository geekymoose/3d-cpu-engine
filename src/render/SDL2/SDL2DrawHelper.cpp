#include "render/SDL2/SDL2DrawHelper.h"


void SDL2DrawHelper::clearSurface(SDL_Surface* surface){
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
}
