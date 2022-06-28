#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_images.h>

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *menu = NULL;

    SDL_Rect positionMenu;
    SDL_Event event;
    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("link.bmp"), NULL);
    ecran = SDL_SetVideoMode(952, 442, 64, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Zelda BOMBER", NULL);

    menu = IMG_Load("menu.png");
    positionMenu.x = 0;
    positionMenu.y = 0;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT :
                continuer = 0;
                break;

            case SDL_KEYDOWN:  
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                
                    default:
                        break;
                }
        
            default :
                break;
        }
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(ecran);
    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}