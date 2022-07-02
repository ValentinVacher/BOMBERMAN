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
    link->direction[haut] = load_image("src/images/link_dos.png", renderer);
    if(link->direction[haut] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return -1;
    }

    link->direction[bas] = load_image("src/images/link_face.png", renderer);
    if(link->direction[bas] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return -1;
    }
    
    link->direction[gauche] = load_image("src/images/link_gauche.png", renderer);
    if(link->direction[gauche] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return -1;
    }

    link->direction[droite] = load_image("src/images/link_droite.png", renderer);
    if(link->direction[droite] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return -1;
    }

    link->forme.x = 0;
    link->forme.y = 0;
    link->forme.w = 90;
    link->forme.h = 115;

    return 0;
}