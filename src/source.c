#include "source.h"

void clean_resources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t)
{
    if(t != NULL)
        SDL_DestroyTexture(t);

    if(r != NULL)
        SDL_DestroyRenderer(r);
    
    if(w != NULL)
        SDL_DestroyWindow(w);

    SDL_Quit();
}