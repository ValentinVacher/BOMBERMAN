#ifndef __APPEL__H__
#define __APPEL__H__

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void destroy_play(SDL_Texture *texture_arriere_plan, Link *link, Link *link_rouge, SDL_Texture *texture_mur, Mix_Music *music);
int play(SDL_Renderer *renderer, Input *in);

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void create_map(Map map[][HAUTEUR]);
SDL_bool print_wall(Map map[][HAUTEUR], SDL_Renderer *renderer, SDL_Texture *texture_mur_destructible);
void detecte_map(Map map[][HAUTEUR], Link *link, const int direction, int joueur);
void deplacer_joueur(Link *link, const int direction);
void creation_bonmbe();
void *gestion_bombe(void *arg);

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void free_link(SDL_Texture *link[]);
int create_link(Link *link, SDL_Renderer *renderer, int joueur);
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *load_image(const char path[], SDL_Renderer *renderer);
int change_music(const int debut, const int duree, int *music_changement, const char path[], Mix_Music *music);
void limite_fps(unsigned int limit, int limite_fps);
void update_event(Input *in);

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif