#ifndef __APPEL__H__
#define __APPEL__H__

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include "constante.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *load_image(const char path[], SDL_Renderer *renderer);
void limite_fps(unsigned int limit, int limite_fps);
void update_event(Input *in);
void free_link(SDL_Texture *link[]);
int create_link(Link *link, SDL_Renderer *renderer);
void deplacer_joueur(Link *link, const int direction, Input *in);
void destroy_play(SDL_Texture *texture_arriere_plan, Link *link, SDL_Texture *texture_mur);
int play(SDL_Renderer *renderer, Input *in);

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif