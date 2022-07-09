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

SDL_bool create_link(Link *link, SDL_Renderer *renderer, int joueur)
{
    if(joueur == LINK)
    {
        link->direction[HAUT] = load_image("src/images/link_dos.png", renderer);
        link->direction[BAS] = load_image("src/images/link_face.png", renderer);
        link->direction[GAUCHE] = load_image("src/images/link_gauche.png", renderer);
        link->direction[DROITE] = load_image("src/images/link_droite.png", renderer);   

        link->forme.x = 135;
        link->forme.y = 15; 

        link->hitbox.x = 140;
        link->hitbox.y = 25;

        link->i = 0;
        link->j = 0;
    }

    else if(joueur == LINK_ROUGE)  
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
        return SDL_FALSE;
    }

    
    if(link->direction[BAS] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return SDL_FALSE;
    }
    
    
    if(link->direction[GAUCHE] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return SDL_FALSE;
    }

   
    if(link->direction[DROITE] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return SDL_FALSE;
    }

    link->hitbox.w = 80;
    link->hitbox.h = 105;

    link->direction_actuel = link->direction[BAS];

    link->nb_bombe_max = 1;
    link->nb_bombe = 0;

    link->bombe.explosion = BOMBE;

    return SDL_TRUE;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void deplacer_joueur(Link *link, const int direction)
{
    link->direction_actuel = link->direction[direction];

    if(direction == HAUT && link->hitbox.y > MUR_HAUTEUR)
    {
        link->forme.y--;
        link->hitbox.y--;
    }

    if(direction == BAS && (link->hitbox.y + link->hitbox.h) < HAUTEUR_WINDOW - MUR_HAUTEUR)
    {
        link->forme.y++;
        link->hitbox.y++;
    }

    if(direction == GAUCHE && link->hitbox.x > MUR_LARGEUR)
    {
        link->forme.x--;
        link->hitbox.x--;
    }

    if(direction == DROITE && (link->hitbox.x + link->hitbox.w) < LARGEUR_WINDOW - MUR_LARGEUR)
    {
        link->forme.x++;
        link->hitbox.x++;
    }
} 

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void creation_bombe(Link *link, pthread_t *thread)
{
    if(link->nb_bombe == 0)
    {
        if(pthread_create(thread, NULL, gestion_bombe, link) != 0)
            SDL_Log("ERREUR : GESTION_BOMBE > %s\n",SDL_GetError());

        link->bombe.i = link->i;
        link->bombe.j = link->j;
        link->nb_bombe++;
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void *gestion_bombe(void *arg)
{
    Link *link = (Link*)arg;

    sleep(1);

    link->bombe.explosion = BOMBE_ROUGE;

    usleep(300000);

    link->bombe.explosion = BOMBE;

    usleep(200000);

    link->bombe.explosion = BOMBE_ROUGE;

    usleep(100000);

    link->bombe.explosion = BOMBE;

    usleep(100000);

    link->bombe.explosion = BOMBE_ROUGE;

    usleep(100000);

    link->bombe.explosion = BOMBE;

    usleep(100000);

    link->bombe.explosion = BOMBE_ROUGE;

    usleep(100000);

    link->bombe.explosion = DESTRUCTION;

    sleep(1);

    link->nb_bombe--;
    link->bombe.explosion = BOMBE;
    
    pthread_exit(NULL);
}