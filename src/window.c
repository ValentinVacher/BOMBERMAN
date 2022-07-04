#include "constante.h"
#include "appel.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR : INIT_VIDEO > %s\n",SDL_GetError());
        return -1;
    }

    if(Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
    {
        SDL_Log("ERREUR : OPEN_AUDIO > %s\n", Mix_GetError());
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

void limite_fps(unsigned int limit, int limite_fps)
{
    unsigned int ticks = SDL_GetTicks();

    if(limit < ticks)
        return;
    
    else if(limit > ticks + limite_fps)
        SDL_Delay(limite_fps);
        
    else 
        SDL_Delay(limit - ticks);
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void update_event(Input *in)
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                in->quit = SDL_TRUE;
                break;

            case SDL_KEYDOWN:
                in->key[event.key.keysym.scancode] = SDL_TRUE;
                break;

            case SDL_KEYUP:
                in->key[event.key.keysym.scancode] = SDL_FALSE;
                break;
            
            case SDL_MOUSEMOTION:
                in->x = event.motion.x;
                in->y = event.motion.y;
                in->xrel = event.motion.xrel;
                in->yrel = event.motion.yrel;
                break;
            
            case SDL_MOUSEWHEEL:
                in->xwheel = event.wheel.x;
                in->ywheel = event.wheel.y;
                break;
            
            case SDL_MOUSEBUTTONDOWN:
                in->mouse[event.button.button] = SDL_TRUE;
                break;

            case SDL_MOUSEBUTTONUP:
                in->mouse[event.button.button] = SDL_FALSE;
                break;
            
            default:
                break;
        }
    }
}