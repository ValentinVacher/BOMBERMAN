#include "constante.h"
#include "appel.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

SDL_bool print_wall(SDL_Rect mur[], int nb_mur, SDL_Renderer *renderer, SDL_Texture *texture_mur)
{
    int i;

    for(i = 0 ; i < nb_mur ; i++)
    {   
        if(SDL_RenderCopy(renderer, texture_mur, NULL, &mur[i]) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            return SDL_FALSE;
        }
    }

    return SDL_TRUE;
}