#include "constante.h"
#include "appel.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void link_sprite(Link *link, const int direction, const SDL_Rect mur[], const int nb_mur)
{
        if(link->colision != droite || link->forme_actuel.y > mur[link->mur].y + mur[link->mur].h || link->forme_actuel.y + link->forme_actuel.h < mur[link->mur].y)
        {
            link->direction_actuel = link->direction[direction];
            link->forme[direction].x = link->forme_actuel.x;
            link->forme[direction].y = link->forme_actuel.y;
            link->forme_actuel = link->forme[direction];
        }
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void destection_colision(Link *link, const int direction, const SDL_Rect mur[], const int nb_mur)
{
    int i;

    for(i = 0 ; i < nb_mur ; i++)
        if(SDL_HasIntersection(&link->forme_actuel, &mur[i]))
        {
            if(direction == haut && link->forme_actuel.y > 0)
                link->forme_actuel.y++;

            if(direction == bas && (link->forme_actuel.y + link->forme_actuel.h) < HAUTEUR)
                link->forme_actuel.y--;

            if(direction == gauche && link->forme_actuel.x > 0)
                link->forme_actuel.x++;

            if(direction == droite && (link->forme_actuel.x + link->forme_actuel.w) < LARGEUR)
                link->forme_actuel.x--;

            link->colision = direction;
            link->mur = i;
            break;
        }
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void deplacer_joueur(Link *link, const int direction, const SDL_Rect mur[], const int nb_mur)
{
    link_sprite(link, direction, mur, nb_mur);

    if(direction == haut && link->forme_actuel.y > 0)
    {
        link->forme_actuel.y--;
    }

    if(direction == bas && (link->forme_actuel.y + link->forme_actuel.h) < HAUTEUR)
    {
        link->forme_actuel.y++;
    }

    if(direction == gauche && link->forme_actuel.x > 0)
    {
        link->forme_actuel.x--;
        link->colision = -1;
    }

    if(direction == droite && (link->forme_actuel.x + link->forme_actuel.w) < LARGEUR)
    {
        link->forme_actuel.x++;
        link->colision = -1;
    }

    destection_colision(link, direction, mur, nb_mur);
}   