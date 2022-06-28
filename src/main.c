#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *menu = NULL;

    SDL_Rect positionMenu;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("link.bmp"), NULL);
    ecran = SDL_SetVideoMode(952, 442, 64, SDL_HWSurface);

    return 0;
}