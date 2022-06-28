#include "source.h"

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Surface *image_menu = NULL;
    SDL_Rect positionMenu = {0, 0, LARGEUR, HAUTEUR};

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("BOMBERMAN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR, HAUTEUR, 0);
    if(window == NULL)
    {
        SDL_Log("ERREUR > %s\n",SDL_GetError());
        clean_resources(window, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(renderer == NULL)
    {
        SDL_Log("ERREUR > %s\n",SDL_GetError());
        clean_resources(window, renderer, NULL);
        exit(EXIT_FAILURE);
    }

    image_menu = IMG_Load("src/images/menu.jpg");
    if(image_menu == NULL)
    {
        SDL_Log("ERREUR > %s\n",SDL_GetError());
        clean_resources(window, renderer, NULL);
        exit(EXIT_FAILURE);
    }

    texture = SDL_CreateTextureFromSurface(renderer, image_menu);
    SDL_FreeSurface(image_menu);
    if(texture == NULL)
    {
        SDL_Log("ERREUR > %s\n",SDL_GetError());
        clean_resources(window, renderer, texture);
        exit(EXIT_FAILURE);
    }

    if(SDL_QueryTexture(texture, NULL, NULL, &positionMenu.w, &positionMenu.h) != 0)
    {
        SDL_Log("ERREUR > %s\n",SDL_GetError());
        clean_resources(window, renderer, texture);
        exit(EXIT_FAILURE);
    }

    if(SDL_RenderCopy(renderer, texture, NULL, &positionMenu) != 0)
    {
        SDL_Log("ERREUR > %s\n",SDL_GetError());
        clean_resources(window, renderer, texture);
        exit(EXIT_FAILURE);
    }

    SDL_bool programme_launched = SDL_TRUE;
    
    while(programme_launched)
    {
        SDL_Event event;

        SDL_RenderPresent(renderer);

        while(SDL_PollEvent(&event) == 1)
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    programme_launched = SDL_FALSE;
                    break;
                
                default:
                    break;
                }
                break;
            
            case SDL_QUIT:
                programme_launched = SDL_FALSE;
                break;

            default:
                break;
            }
        }
    }

    clean_resources(window, renderer, texture);


    return EXIT_SUCCESS;
}