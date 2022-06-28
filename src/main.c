#include "source.h"

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture_menu = NULL;
    SDL_Texture *texture_bouton_quitter = NULL;
    SDL_Surface *image_menu = NULL;
    SDL_Surface *image_bouton_quitter = NULL;
    SDL_Rect positionMenu = {0, 0, LARGEUR, HAUTEUR};
    SDL_Rect position_bouton_quitter = {1200, 600, 500, 100};

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("BOMBERMAN", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR, HAUTEUR, 0);
    if(window == NULL)
    {
        SDL_Log("ERREUR > %s\n",SDL_GetError());
        clean_resources(window, NULL, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(renderer == NULL)
    {
        SDL_Log("ERREUR > %s\n",SDL_GetError());
        clean_resources(window, renderer, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    image_menu = IMG_Load("src/images/menu.jpg");
    if(image_menu == NULL)
    {
        SDL_Log("ERREUR > %s\n",SDL_GetError());
        clean_resources(window, renderer, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    texture_menu = SDL_CreateTextureFromSurface(renderer, image_menu);
    SDL_FreeSurface(image_menu);
    if(texture_menu == NULL)
    {
        SDL_Log("ERREUR > %s\n",SDL_GetError());
        clean_resources(window, renderer, NULL, NULL);
        exit(EXIT_FAILURE);
    }

    if(SDL_QueryTexture(texture_menu, NULL, NULL, &positionMenu.w, &positionMenu.h) != 0)
    {
        SDL_Log("ERREUR > %s\n",SDL_GetError());
        clean_resources(window, renderer, texture_menu, NULL);
        exit(EXIT_FAILURE);
    }

    SDL_bool programme_launched = SDL_TRUE;
    
    while(programme_launched)
    {
        SDL_Event event;

        SDL_RenderClear(renderer);
        image_bouton_quitter = IMG_Load("src/images/bouton_quitter.png");
        if(image_bouton_quitter == NULL)
        {
            SDL_Log("ERREUR > %s\n",SDL_GetError());
            clean_resources(window, renderer, texture_menu, NULL);
            exit(EXIT_FAILURE);
        }

        texture_bouton_quitter = SDL_CreateTextureFromSurface(renderer, image_bouton_quitter);
        SDL_FreeSurface(image_bouton_quitter);
        if(texture_bouton_quitter == NULL)
        {
            SDL_Log("ERREUR > %s\n",SDL_GetError());
            clean_resources(window, renderer, texture_menu, NULL);
            exit(EXIT_FAILURE);
        }

        if(SDL_QueryTexture(texture_bouton_quitter, NULL, NULL, &position_bouton_quitter.w, &position_bouton_quitter.h) != 0)
        {
            SDL_Log("ERREUR > %s\n",SDL_GetError());
            clean_resources(window, renderer, texture_menu, texture_bouton_quitter);
            exit(EXIT_FAILURE);
        }

        if(SDL_RenderCopy(renderer, texture_menu, NULL, &positionMenu) != 0)
        {
            SDL_Log("ERREUR > %s\n",SDL_GetError());
            clean_resources(window, renderer, texture_menu, texture_bouton_quitter);
            exit(EXIT_FAILURE);
        }

        if(SDL_RenderCopy(renderer, texture_bouton_quitter, NULL, &position_bouton_quitter) != 0)
        {
            SDL_Log("ERREUR > %s\n",SDL_GetError());
            clean_resources(window, renderer, texture_menu, texture_bouton_quitter);
            exit(EXIT_FAILURE);
        }

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
                
                case SDLK_1:
                    if(play(renderer, positionMenu))
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
        printf("pipi\n");
    }

    clean_resources(window, renderer, texture_menu, texture_bouton_quitter);


    return EXIT_SUCCESS;
}