#include "source.h"

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR : INIT_VIDEO > %s\n",SDL_GetError());
        return -1;
    }

    if(SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, window, renderer) != 0)
    {
        SDL_Log("ERREUR : CREATE_WINDOW_OR_RENDERER > %s\n",SDL_GetError());
        return -1;
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

SDL_Texture *load_image(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *image = NULL;
    SDL_Texture *texture = NULL;

    image = IMG_Load(path);
    if(image == NULL)
    {
        SDL_Log("ERREUR : LOAD_IMAGE > %s\n",SDL_GetError());
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    if(texture == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        return NULL;
    }
    return texture;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void limite_fps(unsigned int limit)
{
    unsigned int ticks = SDL_GetTicks();

    if(limit < ticks)
        return;
    
    else if(limit > ticks + FPS)
        SDL_Delay(FPS);
    else 
        SDL_Delay(limit - ticks);
}