#include "constante.h"
#include "appel.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void create_map(Map map[][HAUTEUR])
{
    int i, j, nb_block = 0, compteur = 2;

    printf("SEED : %d\n",time(NULL));
    srand(time(NULL));

    map[0][0].type = LINK;
    map[1][0].type = VIDE_CONSTANT;
    map[0][1].type = VIDE_CONSTANT;

    map[LARGEUR - 1][0].type = VIDE_CONSTANT;
    map[LARGEUR - 2][0].type = VIDE_CONSTANT;
    map[LARGEUR - 1][1].type = VIDE_CONSTANT;

    map[0][HAUTEUR - 1].type = VIDE_CONSTANT;
    map[0][HAUTEUR - 2].type = VIDE_CONSTANT;
    map[1][HAUTEUR - 1].type = VIDE_CONSTANT;

    map[LARGEUR - 1][HAUTEUR - 1].type = LINK_ROUGE;
    map[LARGEUR - 2][HAUTEUR - 1].type = VIDE_CONSTANT;
    map[LARGEUR - 1][HAUTEUR - 2].type = VIDE_CONSTANT;

    for(i = 0 ; i < LARGEUR ; i++)
        for(j = 0 ; j < HAUTEUR ; j++)
        {
            map[i][j].coord_case.x = i * 150 + MUR_LARGEUR;
            map[i][j].coord_case.y = j * 150 + MUR_HAUTEUR;
            map[i][j].coord_case.w = 150;
            map[i][j].coord_case.h = 150;

            if(i % 2 != 0 && j % 2 != 0)
                map[i][j].type = MUR_INDESTRUCTIBLE;

            else if(map[i][j].type != VIDE_CONSTANT && map[i][j].type != LINK && map[i][j].type != LINK_ROUGE)  
                map[i][j].type = VIDE;
        }

    while (nb_block < 40)
    {
        for(i = 0 ; i < LARGEUR ; i++)
            for(j = 0 ; j < HAUTEUR ; j++)
                if(map[i][j].type == VIDE && rand() % compteur > 0 && nb_block < 40)
                { 
                    map[i][j].type = MUR_DESTRUCTIBLE;
                    nb_block++;
                }

        compteur++;
    }  
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

SDL_bool print_wall(Map map[][HAUTEUR], SDL_Renderer *renderer, SDL_Texture *texture_mur_destructible)
{
    int i, j;

    for(i = 0 ; i < LARGEUR ; i++) 
        for(j = 0 ; j < HAUTEUR ; j++)
            if(map[i][j].type == MUR_DESTRUCTIBLE)
                if(SDL_RenderCopy(renderer, texture_mur_destructible, NULL, &map[i][j].coord_case) != 0)
                {
                    SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
                    return SDL_FALSE;
                }

    return SDL_TRUE;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void detecte_map(Map map[][HAUTEUR], Link *link, const int direction, int joueur)
{
    int i, j;

    for(i = 0 ; i < LARGEUR ; i++)
        for(j = 0 ; j < HAUTEUR ; j++)
        {
            if(SDL_HasIntersection(&link->hitbox, &map[i][j].coord_case))   
            {
                if(map[i][j].type == VIDE && joueur == LINK)
                    map[i][j].type = LINK;

                else if(map[i][j].type == VIDE && joueur == LINK_ROUGE)
                    map[i][j].type = LINK_ROUGE;

                else if(map[i][j].type == MUR_INDESTRUCTIBLE || map[i][j].type == MUR_DESTRUCTIBLE)
                {
                    if(direction == HAUT)
                    {
                        link->forme.y++;
                        link->hitbox.y++;
                    }

                    else if(direction == BAS)
                    {
                        link->forme.y--;
                        link->hitbox.y--;
                    }

                    else if(direction == GAUCHE)
                    {
                        link->forme.x++;
                        link->hitbox.x++;
                    }

                    else if(direction == DROITE)
                    {
                        link->forme.x--;
                        link->hitbox.x--;
                    }
                }
            }

            else if(map[i][j].type == LINK || map[i][j].type == LINK_ROUGE)
                map[i][j].type = VIDE;
        } 
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

void creation_bonmbe()
{
    pthread_t thread_1;

    if(pthread_create(&thread_1, NULL, gestion_bombe, NULL) != 0)
        SDL_Log("ERREUR : GESTION_BOMBE > %s\n",SDL_GetError());
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void *gestion_bombe(void *arg)
{
    printf("BOMBE_POSER\n");
    sleep(1);
    printf("BOMBE_EXPLOSER\n");

    pthread_exit(NULL);
}