#include "constante.h"
#include "appel.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
void detection_colision(Link *link, const int direction)
{
    int i;

    for(i = 0 ; i < nb_mur ; i++)
        if(SDL_HasIntersection(&link->forme, &mur[i]))
        {
            if(direction == haut && link->forme.y > 0)
                link->forme.y++;

            if(direction == bas && (link->forme.y + link->forme.h) < HAUTEUR)
                link->forme.y--;

            if(direction == gauche && link->forme.x > 0)
                link->forme.x++;

            if(direction == droite && (link->forme.x + link->forme.w) < LARGEUR)
                link->forme.x--;

            break;
        }
}*/

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void deplacer_joueur(Link *link, const int direction)
{
    link->direction_actuel = link->direction[direction];

    if(direction == haut && link->forme.y > 0)
    {
        link->forme.y--;
    }

    if(direction == bas && (link->forme.y + link->forme.h) < HAUTEUR)
    {
        link->forme.y++;
    }

    if(direction == gauche && link->forme.x > 0)
    {
        link->forme.x--;
    }

    if(direction == droite && (link->forme.x + link->forme.w) < LARGEUR)
    {
        link->forme.x++;
    }

    //detection_colision(link, direction);
}   