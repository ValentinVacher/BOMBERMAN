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
    int i;

    for(i = 0 ; i < 4 ; i++)
    {
        link->forme[i].x = 0;
        link->forme[i].y = 0;
    }

    for(i = 2 ; i < 4 ; i++)
    {
        link->forme[i].h = 110;
        link->forme[i].w = 85;
        link->forme[i - 2].w = 90;
    }

    link->direction[haut] = load_image("src/images/link_dos.png", renderer);
    if(link->direction[haut] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return -1;
    }
    link->forme[haut].h = 105;

    link->direction[bas] = load_image("src/images/link_face.png", renderer);
    if(link->direction[bas] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return -1;
    }
    link->forme[bas].h = 115;
    
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

    return 0;
}