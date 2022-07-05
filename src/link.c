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

int create_link(Link *link, SDL_Renderer *renderer, int joueur)
{
    if(joueur == VERT)
    {
        link->direction[HAUT] = load_image("src/images/link_dos.png", renderer);
        link->direction[BAS] = load_image("src/images/link_face.png", renderer);
        link->direction[GAUCHE] = load_image("src/images/link_gauche.png", renderer);
        link->direction[DROITE] = load_image("src/images/link_droite.png", renderer);   

        link->forme.x = 135;
        link->forme.y = 15; 

        link->hitbox.x = 140;
        link->hitbox.y = 25;
    }

    else if(joueur == ROUGE)  
    {
        link->direction[HAUT] = load_image("src/images/link_dos_rouge.png", renderer);
        link->direction[BAS] = load_image("src/images/link_face_rouge.png", renderer);
        link->direction[GAUCHE] = load_image("src/images/link_gauche_rouge.png", renderer);
        link->direction[DROITE] = load_image("src/images/link_droite_rouge.png", renderer); 

        link->forme.x = 135 + 1650 - 90;
        link->forme.y = 15 + 1050 - 115; 

        link->hitbox.x = 140 + 1650 - 90;
        link->hitbox.y = 25 + 1050 - 115;
    }

    if(link->direction[HAUT] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return -1;
    }

    
    if(link->direction[BAS] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return -1;
    }
    
    
    if(link->direction[GAUCHE] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return -1;
    }

   
    if(link->direction[DROITE] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return -1;
    }

    link->hitbox.w = 80;
    link->hitbox.h = 105;

    link->direction_actuel = link->direction[BAS];

    return 0;
}