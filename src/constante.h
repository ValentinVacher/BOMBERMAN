#ifndef __CONSTANTE__H__
#define __CONSTANTE__H__

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define LARGEUR_WINDOW 1920
#define HAUTEUR_WINDOW 1080
#define MUR_LARGEUR 135
#define MUR_HAUTEUR 15
#define LARGEUR 11
#define HAUTEUR 7
#define FPS 16

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

enum
{
    HAUT,//0
    BAS,//1
    GAUCHE,//2
    DROITE//3
};

enum
{
    VIDE,//0
    MUR_INDESTRUCTIBLE,//1
    LINK,//2
    MUR_DESTRUCTIBLE,//3
    VIDE_CONSTANT,//4
    LINK_ROUGE,//5
    BOMBE_MAP,//6
    FUTURE_BOMBE//7
};

enum
{
    BOMBE,//0
    BOMBE_ROUGE,//1
    DESTRUCTION,//2
    EXPLOSION//3
};

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

typedef struct Input
{
    SDL_bool key[SDL_NUM_SCANCODES];
    SDL_bool quit;
    int x, y, xrel, yrel;
    int xwheel, ywheel;
    SDL_bool mouse[6];
}Input;

typedef struct Bombe
{
    int i,j, explosion;
    SDL_bool son;
}Bombe;

typedef struct Link
{
    SDL_Texture *direction[4], *direction_actuel;
    SDL_Rect forme, hitbox;
    int nb_bombe, nb_bombe_max, i, j, couileur;
    Bombe bombe;
}Link;

typedef struct Map
{
    SDL_Rect coord_case;
    int type;
}Map;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif