#include "constante.h"
#include "appel.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void create_map(SDL_Renderer *renderer, SDL_Texture *texture_mur, Map map[][HAUTEUR / 150])
{
    int i, j;

    for(i = 0 ; i < LARGEUR / 150 ; i++)
    {
        for(j = 0 ; j < HAUTEUR / 150 ; j++)
        {
            map[i][j].case.x = i * 150;
            map[i][j].case.y = j * 150;
            map[i][j].case.x = 150;
            map[i][j].case.x = 150;

            if(i % 2 != 0 && j % 2 != 0)
            {
                map[i][j].type = mur_indestructible;
            }
            else    
                map[i][j].type = vide;
        }
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

SDL_bool print_wall(Map map[][HAUTEUR / 150], SDL_Renderer *renderer, SDL_Texture *texture_mur)
{
    int i, j;

    for(i = 0 ; i < LARGEUR / 150 ; i++)
    {   
        for(j = 0 ; j < HAUTEUR / 150 ; j++)
            if(map[i][j].type == mur_indestructible)
                if(SDL_RenderCopy(renderer, texture_mur, NULL, &map[i][j].case) != 0)
                {
                    SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
                    return SDL_FALSE;
                }
    }

    return SDL_TRUE;
}