#include "constante.h"
#include "appel.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void create_map(Map map[][HAUTEUR / 150])
{
    int i, j;

    for(i = 0 ; i < LARGEUR / 150 ; i++)
        for(j = 0 ; j < HAUTEUR / 150 ; j++)
        {
            map[i][j].coord_case.x = i * 150;
            map[i][j].coord_case.y = j * 150;
            map[i][j].coord_case.w = 150;
            map[i][j].coord_case.h = 150;

            if(i % 2 != 0 && j % 2 != 0)
            {
                map[i][j].type = MUR_INDESTRUCTIBLE;
            }
            else    
                map[i][j].type = MUR_DESTRUCTIBLE;
        }

    map[0][0].type = LINK;
    map[1][0].type = VIDE;
    map[0][1].type = VIDE;

    map[LARGEUR / 150 - 1][0].type = VIDE;
    map[LARGEUR / 150 - 2][0].type = VIDE;
    map[LARGEUR / 150 - 1][1].type = VIDE;

    map[0][HAUTEUR / 150 - 1].type = VIDE;
    map[0][HAUTEUR / 150 - 2].type = VIDE;
    map[1][HAUTEUR / 150 - 1].type = VIDE;

    map[LARGEUR / 150 - 1][HAUTEUR / 150 - 1].type = VIDE;
    map[LARGEUR / 150 - 2][HAUTEUR / 150 - 1].type = VIDE;
    map[LARGEUR / 150 - 1][HAUTEUR / 150 - 2].type = VIDE;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

SDL_bool print_wall(Map map[][HAUTEUR / 150], SDL_Renderer *renderer, SDL_Texture *texture_mur_destructible)
{
    int i, j;

    for(i = 0 ; i < LARGEUR / 150 ; i++) 
        for(j = 0 ; j < HAUTEUR / 150 ; j++)
            if(map[i][j].type == MUR_DESTRUCTIBLE)
                if(SDL_RenderCopy(renderer, texture_mur_destructible, NULL, &map[i][j].coord_case) != 0)
                {
                    SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
                    return SDL_FALSE;
                }

    return SDL_TRUE;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void detecte_map(Map map[][HAUTEUR / 150], Link *link, const int direction)
{
    int i, j;

    for(i = 0 ; i < LARGEUR / 150 ; i++)
        for(j = 0 ; j < HAUTEUR / 150 ; j++)
        {
            if(SDL_HasIntersection(&link->hitbox, &map[i][j].coord_case))   
            {
                if(map[i][j].type == VIDE)
                    map[i][j].type = LINK;

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

            else if(map[i][j].type == LINK)
                map[i][j].type = VIDE;
        } 
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void deplacer_joueur(Link *link, const int direction)
{
    link->direction_actuel = link->direction[direction];

    if(direction == HAUT && link->forme.y > 0)
    {
        link->forme.y--;
        link->hitbox.y--;
    }

    if(direction == BAS && (link->forme.y + link->forme.h) < HAUTEUR)
    {
        link->forme.y++;
        link->hitbox.y++;
    }

    if(direction == GAUCHE && link->forme.x > 0)
    {
        link->forme.x--;
        link->hitbox.x--;
    }

    if(direction == DROITE && (link->forme.x + link->forme.w) < LARGEUR)
    {
        link->forme.x++;
        link->hitbox.x++;
    }
} 