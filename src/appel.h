#ifndef __APPEL__H__
#define __APPEL__H__

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void destroy_play(SDL_Texture *texture_arriere_plan, Link *link, SDL_Texture *texture_mur);
int play(SDL_Renderer *renderer, Input *in);

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void link_sprite(Link *link, const int direction, const SDL_Rect mur[], const int nb_mur);
void destection_colision(Link *link, const int direction, const SDL_Rect mur[], const int _nb_mur);
void deplacer_joueur(Link *link, const int direction, const SDL_Rect mur[], const int nb_mur);

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

SDL_bool print_wall(SDL_Rect mur[], int nb_mur, SDL_Renderer *renderer, SDL_Texture *texture_mur);

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void free_link(SDL_Texture *link[]);
int create_link(Link *link, SDL_Renderer *renderer);

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *load_image(const char path[], SDL_Renderer *renderer);
void limite_fps(unsigned int limit, int limite_fps);
void update_event(Input *in);

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif