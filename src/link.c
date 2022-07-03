#include "constante.h"
#include "appel.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void free_link(SDL_Texture *link[])
{
    int i;

    for(i = 0 ; i < 4 ; i++) 
        if(link[i] != NULL)
            SDL_DestroyTexture(link[i]);
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int create_link(Link *link, SDL_Renderer *renderer)
{
    link->direction[HAUT] = load_image("src/images/link_dos.png", renderer);
    if(link->direction[HAUT] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return -1;
    }

    link->direction[BAS] = load_image("src/images/link_face.png", renderer);
    if(link->direction[BAS] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return -1;
    }
    
    link->direction[GAUCHE] = load_image("src/images/link_gauche.png", renderer);
    if(link->direction[GAUCHE] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return -1;
    }

    link->direction[DROITE] = load_image("src/images/link_droite.png", renderer);
    if(link->direction[DROITE] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return -1;
    }

    link->forme.x = 135;
    link->forme.y = 15;

    link->hitbox.x = 140;
    link->hitbox.y = 25;
    link->hitbox.w = 80;
    link->hitbox.h = 105;

    link->direction_actuel = link->direction[BAS];

    return 0;
}