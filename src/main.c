#include "source.h"

//gcc .\src\*.c -o .\bin\main -I include -L .\lib\ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture_menu = NULL;
    SDL_Surface *image_menu = NULL;
    SDL_bool programme_launched = SDL_TRUE;
    unsigned int frame_limit = 0;
    int statut = EXIT_FAILURE;

    if(init(&window, &renderer, LARGEUR, HAUTEUR) != 0)
        goto quit;

    texture_menu = load_image("src/images/menu.jpg", renderer);
    if(texture_menu == NULL)
        goto quit;

    if(SDL_QueryTexture(texture_menu, NULL, NULL, NULL, NULL) != 0)
    {
        SDL_Log("ERREUR : QUERY_TEXTURE > %s\n",SDL_GetError());
        goto quit;
    }
    
    while(programme_launched)
    {
        frame_limit = SDL_GetTicks() + FPS;

        SDL_Event event;

        if(SDL_RenderCopy(renderer, texture_menu, NULL, NULL) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            goto quit;
        }

        SDL_RenderPresent(renderer);

        while(SDL_PollEvent(&event))
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
                    SDL_DestroyTexture(texture_menu);
                    if(play(renderer))
                        programme_launched = SDL_FALSE;
                    
                    else
                    {
                        texture_menu = load_image("src/images/menu.jpg", renderer);
                        if(texture_menu == NULL)
                            goto quit;
                    }

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

        limite_fps(frame_limit);
    }

    statut = EXIT_SUCCESS;

    quit:

    if(texture_menu != NULL)    
        SDL_DestroyTexture(texture_menu);

    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);

    if(window != NULL)
        SDL_DestroyWindow(window);

    return statut;
}