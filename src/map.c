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

SDL_bool bombe(SDL_Texture *texture_bombe[], SDL_Renderer *renderer, Link *link, Link *link2, Map map[][HAUTEUR], Mix_Chunk *explosion, int *victoire)
{
    if(link->nb_bombe == 1 && link->bombe.explosion == BOMBE)
    {
        if(SDL_RenderCopy(renderer, texture_bombe[0], NULL, &map[link->bombe.i][link->bombe.j].coord_case) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            return SDL_FALSE;
        }
    }

    else if (link->bombe.explosion == BOMBE_ROUGE)
    {
        if(SDL_RenderCopy(renderer, texture_bombe[2], NULL, &map[link->bombe.i][link->bombe.j].coord_case) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            return SDL_FALSE;
        }
    }
    
    else if(link->bombe.explosion == DESTRUCTION)
    {
        if(map[link->bombe.i + 1][link->bombe.j].type == MUR_DESTRUCTIBLE && link->bombe.i + 1 < LARGEUR)
            map[link->bombe.i + 1][link->bombe.j].type = VIDE;
        
        if(map[link->bombe.i - 1][link->bombe.j].type == MUR_DESTRUCTIBLE && link->bombe.i - 1 >= 0)
            map[link->bombe.i - 1][link->bombe.j].type = VIDE;

        if(map[link->bombe.i][link->bombe.j + 1].type == MUR_DESTRUCTIBLE && link->bombe.j + 1 < HAUTEUR)
            map[link->bombe.i][link->bombe.j + 1].type = VIDE;

        if(map[link->bombe.i][link->bombe.j - 1].type == MUR_DESTRUCTIBLE && link->bombe.j - 1 >= 0)
            map[link->bombe.i][link->bombe.j - 1].type = VIDE;

        if(*victoire == 0)
        {
            if(link->i == link->bombe.i && link->j == link->bombe.j)
                *victoire = link2->couleur;
            
            else if(link2->i == link->bombe.i && link2->j == link->bombe.j)
                *victoire = link->couleur;

            else if(map[link->bombe.i + 1][link->bombe.j].type == LINK)
                *victoire = link2->couleur;
            
            else if(map[link->bombe.i + 1][link->bombe.j].type == LINK_ROUGE)
                *victoire = link->couleur;

            else if(map[link->bombe.i - 1][link->bombe.j].type == LINK)
                *victoire = link2->couleur;

            else if(map[link->bombe.i - 1][link->bombe.j].type == LINK_ROUGE)
                *victoire = link->couleur;

            else if(map[link->bombe.i][link->bombe.j + 1].type == LINK)
                *victoire = link2->couleur;

            else if(map[link->bombe.i][link->bombe.j + 1].type == LINK_ROUGE)
                *victoire = link->couleur;

            else if(map[link->bombe.i][link->bombe.j - 1].type == LINK)
                *victoire = link2->couleur;

            else if(map[link->bombe.i][link->bombe.j - 1].type == LINK_ROUGE)
                *victoire = link->couleur;
        }
  
        link->bombe.explosion = EXPLOSION;
    }

    if(link->bombe.explosion == EXPLOSION)
    {
        if(SDL_RenderCopy(renderer, texture_bombe[1], NULL, &map[link->bombe.i][link->bombe.j].coord_case) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            return SDL_FALSE;
        }

        if(map[link->bombe.i + 1][link->bombe.j].type != MUR_INDESTRUCTIBLE && link->bombe.i + 1 < LARGEUR)
        {
            if(SDL_RenderCopy(renderer, texture_bombe[1], NULL, &map[link->bombe.i + 1][link->bombe.j].coord_case) != 0)
            {
                SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
                return SDL_FALSE;
            }
        }
        
        if(map[link->bombe.i - 1][link->bombe.j].type != MUR_INDESTRUCTIBLE && link->bombe.i - 1 >= 0)
        {
            if(SDL_RenderCopy(renderer, texture_bombe[1], NULL, &map[link->bombe.i - 1][link->bombe.j].coord_case) != 0)
            {
                SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
                return SDL_FALSE;
            }
        }

        if(map[link->bombe.i][link->bombe.j + 1].type != MUR_INDESTRUCTIBLE && link->bombe.j + 1 < HAUTEUR)
        {
            if(SDL_RenderCopy(renderer, texture_bombe[1], NULL, &map[link->bombe.i][link->bombe.j + 1].coord_case) != 0)
            {
                SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
                return SDL_FALSE;
            }   
        }

        if(map[link->bombe.i][link->bombe.j - 1].type != MUR_INDESTRUCTIBLE && link->bombe.j - 1 >= 0)
        {
            if(SDL_RenderCopy(renderer, texture_bombe[1], NULL, &map[link->bombe.i][link->bombe.j - 1].coord_case) != 0)
            {
                SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
                return SDL_FALSE;
            }
        }
    }

    if(link->bombe.son)
    {
        Mix_PlayChannel(-1, explosion, 0);
        link->bombe.son = SDL_FALSE;
    }

    return SDL_TRUE;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void detecte_map(Map map[][HAUTEUR], Link *link, Link *link2, const int direction, int joueur)
{
    int i, j;
    SDL_Rect test_hitbox;

    for(i = 0 ; i < LARGEUR ; i++)
        for(j = 0 ; j < HAUTEUR ; j++)
        {
            if(SDL_IntersectRect(&link->hitbox, &map[i][j].coord_case, &test_hitbox))   
            {   
                if(map[i][j].type == MUR_INDESTRUCTIBLE || map[i][j].type == MUR_DESTRUCTIBLE || map[i][j].type == BOMBE_MAP || SDL_HasIntersection(&link->hitbox, &link2->hitbox))
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

                else if(test_hitbox.w * test_hitbox.h > 4200)
                {
                    link->i = i;
                    link->j = j;
                }

                if(map[i][j].type != MUR_DESTRUCTIBLE && map[i][j].type != MUR_INDESTRUCTIBLE)
                    map[i][j].type = link->couleur;
            }

            else if(map[i][j].type == link->couleur)
                map[i][j].type = VIDE;

            if(link->bombe.i == i && link->bombe.j == j)
            {
                if(link->nb_bombe == 1 && !SDL_HasIntersection(&link->hitbox, &map[i][j].coord_case) && !SDL_HasIntersection(&link2->hitbox, &map[i][j].coord_case))
                    map[i][j].type = BOMBE_MAP;

                else if(link->nb_bombe == 0)
                    map[i][j].type = VIDE;
            }
            
            else if(map[i][j].type == BOMBE_MAP) 
                map[i][j].type = VIDE;
        } 
}