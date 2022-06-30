#ifndef __SOURCE__H__
#define __SOURCE__H__

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define LARGEUR 1920
#define HAUTEUR 1080
#define FPS 16
#define DEPLACEMENT 10

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


typedef struct input
{
    SDL_bool key[SDL_NUM_SCANCODES];
    SDL_bool quit;
    int x, y, xrel, yrel;
    int xwheel, ywheel;
    SDL_bool mouse[6];
}input;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *load_image(const char path[], SDL_Renderer *renderer);
void limite_fps(unsigned int limit);
void update_event(input *in);
void free_link(SDL_Texture *link[]);
int create_link(SDL_Texture *link[], SDL_Renderer *renderer, SDL_Rect taille_link[]);
void deplacer_joueur(SDL_Rect *position_link, const int direction);
void destroy_play(SDL_Texture *texture_arriere_plan, SDL_Texture *link_actuel, SDL_Texture *link[]);
int play(SDL_Renderer *renderer, input *in);

#endif