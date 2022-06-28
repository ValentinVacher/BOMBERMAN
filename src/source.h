#ifndef __SOURCE__H__
#define __SOURCE__H__

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#define LARGEUR 1920
#define HAUTEUR 1080

void clean_resources(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture_menu, SDL_Texture *texture_bouton_quitter);
int play(SDL_Renderer *renderer, SDL_Rect taille_renderer);

#endif