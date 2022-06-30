#ifndef __SOURCE__H__
#define __SOURCE__H__

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define LARGEUR 1920
#define HAUTEUR 1080
#define FPS 1000 / 60

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

enum
{
    haut,//0
    bas,//1
    gauche,//2
    droite//3
};

enum
{
    vide,//0
    mur,//1
    link//2
};

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *load_image(const char path[], SDL_Renderer *renderer);
void limite_fps(unsigned int limit);
void free_link(SDL_Texture *link[]);
int create_link(SDL_Texture *link[], SDL_Renderer *renderer, SDL_Rect taille_link[]);
void destroy_play(SDL_Texture *texture_arriere_plan, SDL_Texture *link_actuel, SDL_Texture *link[]);
int play(SDL_Renderer *renderer);

#endif