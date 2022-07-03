#include "constante.h"
#include "appel.h"

//gcc .\src\*.c -o .\bin\main -I include -L .\lib\ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture_menu = NULL;
    SDL_Surface *image_menu = NULL;
    SDL_bool programme_launched = SDL_TRUE;
    Input in;
    unsigned int frame_limit = 0;
    int statut = EXIT_FAILURE;

    memset(&in, SDL_FALSE, sizeof(Input));

    if(init(&window, &renderer, LARGEUR_WINDOW, HAUTEUR_WINDOW) != 0)
        goto quit;

    texture_menu = load_image("src/images/menu.jpg", renderer);
    if(texture_menu == NULL)
        goto quit;

    if(SDL_QueryTexture(texture_menu, NULL, NULL, NULL, NULL) != 0)
    {
        SDL_Log("ERREUR : QUERY_TEXTURE > %s\n",SDL_GetError());
        goto quit;
    }
    
    while(!in.quit)
    {
        frame_limit = SDL_GetTicks() + FPS;

        if(SDL_RenderCopy(renderer, texture_menu, NULL, NULL) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            goto quit;
        }

        SDL_RenderPresent(renderer);

        update_event(&in);

        if(in.key[40])
        {
            SDL_DestroyTexture(texture_menu);
            play(renderer, &in);  
            texture_menu = load_image("src/images/menu.jpg", renderer);
            if(texture_menu == NULL)
                goto quit;
        }
        limite_fps(frame_limit, FPS);
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