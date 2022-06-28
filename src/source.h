#ifndef __SOURCE__H__
#define __SOURCE__H__

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#define LARGEUR 1920
#define HAUTEUR 1080

void clean_resources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);
int play(SDL_Renderer *renderer, SDL_Rect taille_renderer);

#endif