#include "source.h"

void free_link(SDL_Texture *link[])
{
    int i;

    for(i = 0 ; i < 4 ; i++) 
        if(link[i] != NULL)
            SDL_DestroyTexture(link[i]);
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int create_link(SDL_Texture *link[], SDL_Renderer *renderer, SDL_Rect taille_link[])
{
    int i;

    for(i = 0 ; i < 4 ; i++)
    {
        taille_link[i].x = 0;
        taille_link[i].y = 0;
    }

    for(i = 2 ; i < 4 ; i++)
    {
        taille_link[i].h = 110;
        taille_link[i].w = 85;
        taille_link[i - 2].w = 90;
    }

    link[0] = load_image("src/images/link_dos.png", renderer);
    if(link[0] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link);
        return -1;
    }
    taille_link[0].h = 105;

    link[1] = load_image("src/images/link_face.png", renderer);
    if(link[1] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link);
        return -1;
    }
    taille_link[1].h = 115;
    
    link[2] = load_image("src/images/link_gauche.png", renderer);
    if(link[2] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link);
        return -1;
    }

    link[3] = load_image("src/images/link_droite.png", renderer);
    if(link[3] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link);
        return -1;
    }

    return 0;
}