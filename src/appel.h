#ifndef __APPEL__H__
#define __APPEL__H__

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int play(SDL_Renderer *renderer, Input *in);

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void create_map(Map map[][HAUTEUR]);
SDL_bool print_wall(Map map[][HAUTEUR], SDL_Renderer *renderer, SDL_Texture *texture_mur_destructible);
void detecte_map(Map map[][HAUTEUR], Link *link, Link *link2, const int direction, int joueur);
SDL_bool pose_bombe(SDL_Texture *texture_bombe[], SDL_Renderer *renderer, Link *link, Link *link2, Map map[][HAUTEUR], Mix_Chunk *explosion, int *victoire);

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void free_link(SDL_Texture *link[]);
SDL_bool create_link(Link *link, SDL_Renderer *renderer, int joueur);
void deplacer_joueur(Link *link, const int direction);
void creation_bombe(Link *link, pthread_t *thread, Map map[][HAUTEUR]);
void *gestion_bombe(void *arg);
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);
SDL_Texture *load_image(const char path[], SDL_Renderer *renderer);
int change_music(const int debut, const int duree, int *music_changement, const char path[], Mix_Music *music);
void limite_fps(unsigned int limit, int limite_fps);
void update_event(Input *in);

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif