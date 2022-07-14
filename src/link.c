#include "constante.h"
#include "appel.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void free_link(SDL_Texture *link[][11])
{
    int i, j;

    for(i = 0 ; i < 4 ; i++) 
        for(j = 0 ; j < 11 ; j++)
            if(link[i][j] != NULL)
            {
                SDL_DestroyTexture(link[i][0]);
                printf("DESTROY_TEXTURE : LINK.DIRECTION[%d][%d]\n", i, j);
            }
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

SDL_bool create_link(Link *link, SDL_Renderer *renderer, int joueur)
{
    if(joueur == LINK)
    {
        link->direction[HAUT][0] = load_image("src/images/link_dos.png", renderer);
        link->direction[HAUT][1] = load_image("src/images/animation_link/link_haut_1.png", renderer);
        link->direction[HAUT][2] = load_image("src/images/animation_link/link_haut_2.png", renderer);
        link->direction[HAUT][3] = load_image("src/images/animation_link/link_haut_3.png", renderer);
        link->direction[HAUT][4] = load_image("src/images/animation_link/link_haut_4.png", renderer);
        link->direction[HAUT][5] = load_image("src/images/animation_link/link_haut_5.png", renderer);
        link->direction[HAUT][6] = load_image("src/images/animation_link/link_haut_6.png", renderer);
        link->direction[HAUT][7] = load_image("src/images/animation_link/link_haut_7.png", renderer);
        link->direction[HAUT][8] = load_image("src/images/animation_link/link_haut_8.png", renderer);
        link->direction[HAUT][9] = load_image("src/images/animation_link/link_haut_9.png", renderer);
        link->direction[HAUT][10] = load_image("src/images/animation_link/link_haut_10.png", renderer);

        link->direction[BAS][0] = load_image("src/images/link_face.png", renderer);
        link->direction[BAS][1] = load_image("src/images/animation_link/link_bas_1.png", renderer);
        link->direction[BAS][2] = load_image("src/images/animation_link/link_bas_2.png", renderer);
        link->direction[BAS][3] = load_image("src/images/animation_link/link_bas_3.png", renderer);
        link->direction[BAS][4] = load_image("src/images/animation_link/link_bas_4.png", renderer);
        link->direction[BAS][5] = load_image("src/images/animation_link/link_bas_5.png", renderer);
        link->direction[BAS][6] = load_image("src/images/animation_link/link_bas_6.png", renderer);
        link->direction[BAS][7] = load_image("src/images/animation_link/link_bas_7.png", renderer);
        link->direction[BAS][8] = load_image("src/images/animation_link/link_bas_8.png", renderer);
        link->direction[BAS][9] = load_image("src/images/animation_link/link_bas_9.png", renderer);
        link->direction[BAS][10] = load_image("src/images/animation_link/link_bas_10.png", renderer);

        link->direction[GAUCHE][0] = load_image("src/images/link_gauche.png", renderer);
        link->direction[GAUCHE][1] = load_image("src/images/animation_link/link_gauche_1.png", renderer);
        link->direction[GAUCHE][2] = load_image("src/images/animation_link/link_gauche_2.png", renderer);
        link->direction[GAUCHE][3] = load_image("src/images/animation_link/link_gauche_3.png", renderer);
        link->direction[GAUCHE][4] = load_image("src/images/animation_link/link_gauche_4.png", renderer);
        link->direction[GAUCHE][5] = load_image("src/images/animation_link/link_gauche_5.png", renderer);
        link->direction[GAUCHE][6] = load_image("src/images/animation_link/link_gauche_6.png", renderer);
        link->direction[GAUCHE][7] = load_image("src/images/animation_link/link_gauche_7.png", renderer);
        link->direction[GAUCHE][8] = load_image("src/images/animation_link/link_gauche_8.png", renderer);
        link->direction[GAUCHE][9] = load_image("src/images/animation_link/link_gauche_9.png", renderer);
        link->direction[GAUCHE][10] = load_image("src/images/animation_link/link_gauche_10.png", renderer);


        link->direction[DROITE][0] = load_image("src/images/link_droite.png", renderer); 
        link->direction[DROITE][2] = load_image("src/images/animation_link/link_droit_2.png", renderer);
        link->direction[DROITE][1] = load_image("src/images/animation_link/link_droit_1.png", renderer);
        link->direction[DROITE][3] = load_image("src/images/animation_link/link_droit_3.png", renderer);
        link->direction[DROITE][4] = load_image("src/images/animation_link/link_droit_4.png", renderer);
        link->direction[DROITE][5] = load_image("src/images/animation_link/link_droit_5.png", renderer);
        link->direction[DROITE][6] = load_image("src/images/animation_link/link_droit_6.png", renderer);
        link->direction[DROITE][7] = load_image("src/images/animation_link/link_droit_7.png", renderer);
        link->direction[DROITE][8] = load_image("src/images/animation_link/link_droit_8.png", renderer);
        link->direction[DROITE][9] = load_image("src/images/animation_link/link_droit_9.png", renderer);
        link->direction[DROITE][10] = load_image("src/images/animation_link/link_droit_10.png", renderer);  

        link->forme.x = 135;
        link->forme.y = 15; 

        link->hitbox.x = 140;
        link->hitbox.y = 25;

        link->i = 0;
        link->j = 0;

        link->couleur = LINK;
    }

    else if(joueur == LINK_ROUGE)  
    {
        link->direction[HAUT][0] = load_image("src/images/link_dos_rouge.png", renderer);
        link->direction[BAS][0] = load_image("src/images/link_face_rouge.png", renderer);
        link->direction[GAUCHE][0] = load_image("src/images/link_gauche_rouge.png", renderer);
        link->direction[DROITE][0] = load_image("src/images/link_droite_rouge.png", renderer); 

        link->forme.x = 135 + 1650 - 90;
        link->forme.y = 15 + 1050 - 115; 

        link->hitbox.x = 140 + 1650 - 90;
        link->hitbox.y = 25 + 1050 - 115;

        link->i = 10;
        link->j = 6;

        link->couleur = LINK_ROUGE;
    }

    if(link->direction[HAUT][0] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return SDL_FALSE;
    }

    
    if(link->direction[BAS][0] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return SDL_FALSE;
    }
    
    
    if(link->direction[GAUCHE][0] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return SDL_FALSE;
    }

   
    if(link->direction[DROITE][0] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link->direction);
        return SDL_FALSE;
    }

    link->hitbox.w = 80;
    link->hitbox.h = 105;

    link->direction_actuel = link->direction[BAS][0];

    link->nb_bombe_max = 1;
    link->nb_bombe = 0;

    link->bombe.explosion = BOMBE;
    link->bombe.son = SDL_FALSE;

    link->animation = 0;

    return SDL_TRUE;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void deplacer_joueur(Link *link, const int direction)
{
    link->direction_actuel = link->direction[direction][link->animation / 100];

    if(direction == HAUT && link->hitbox.y > MUR_HAUTEUR)
    {
        link->forme.y--;
        link->hitbox.y--;
    }

    else if(direction == BAS && (link->hitbox.y + link->hitbox.h) < HAUTEUR_WINDOW - MUR_HAUTEUR)
    {
        link->forme.y++;
        link->hitbox.y++;
    }

    else if(direction == GAUCHE && link->hitbox.x > MUR_LARGEUR)
    {
        link->forme.x--;
        link->hitbox.x--;
    }

    else if(direction == DROITE && (link->hitbox.x + link->hitbox.w) < LARGEUR_WINDOW - MUR_LARGEUR)
    {
        link->forme.x++;
        link->hitbox.x++;
    }
} 

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void creation_bombe(Link *link, pthread_t *thread, Map map[][HAUTEUR])
{
    if(link->nb_bombe == 0 && map[link->i][link->j].type != FUTURE_BOMBE)
    {
        if(pthread_create(thread, NULL, gestion_bombe, link) != 0)
            SDL_Log("ERREUR : GESTION_BOMBE > %s\n",SDL_GetError());

        map[link->i][link->j].type = FUTURE_BOMBE;
        link->bombe.i = link->i;
        link->bombe.j = link->j;
        link->nb_bombe++;
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void *gestion_bombe(void *arg)
{
    Link *link = (Link*)arg;
    int i;

    sleep(1);

    link->bombe.explosion = BOMBE_ROUGE;

    usleep(300000);

    link->bombe.explosion = BOMBE;

    usleep(200000);

    link->bombe.explosion = BOMBE_ROUGE;

    for(i = 0 ; i < 2 ; i++)
    {
        usleep(100000);
        link->bombe.explosion = BOMBE;

        usleep(100000);
        link->bombe.explosion = BOMBE_ROUGE;
    }

    usleep(100000);

    link->bombe.explosion = DESTRUCTION;
    link->bombe.son = SDL_TRUE;

    usleep(500000);

    link->nb_bombe--;
    link->bombe.explosion = BOMBE;
    
    pthread_exit(NULL);
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void link_animation(int *animation)
{
    *animation += 2;
        if(*animation > 1000)
            *animation = 100;
}