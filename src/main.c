#include "constante.h"
#include "appel.h"

//gcc .\src\*.c -o .\bin\main -I include -L .\lib\ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture_menu = NULL;
    SDL_Surface *image_menu = NULL;
    SDL_bool programme_launched = SDL_TRUE;
    Input in;
    Mix_Music *music;
    unsigned int frame_limit = 0;
    int statut = EXIT_FAILURE;

    printf("test\n");

    memset(&in, SDL_FALSE, sizeof(Input));

    if(init(&window, &renderer, LARGEUR_WINDOW, HAUTEUR_WINDOW) != 0)
        goto quit;

    music = Mix_LoadMUS("src/musiques/the-legend-of-zelda-links-awakening-ost-overworld.mp3");
    if(music == NULL)
    {
        SDL_Log("ERREUR : LOAD_MUS > %s\n", Mix_GetError());
        goto quit;
    }

    texture_menu = load_image("src/images/menu.jpg", renderer);
    if(texture_menu == NULL)
        goto quit;

    if(SDL_QueryTexture(texture_menu, NULL, NULL, NULL, NULL) != 0)
    {
        SDL_Log("ERREUR : QUERY_TEXTURE > %s\n", SDL_GetError());
        goto quit;
    }

    if(Mix_PlayMusic(music, -1) != 0)
    {
        SDL_Log("ERREUR : PLAY_MUSIC > %s\n", Mix_GetError());
        goto quit;
    }

    printf("test\n");
    
    while(!in.quit)
    {
        frame_limit = SDL_GetTicks() + FPS;

        if(SDL_RenderCopy(renderer, texture_menu, NULL, NULL) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n", SDL_GetError());
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

    if(music != NULL)
        Mix_FreeMusic(music);

    if(texture_menu != NULL)    
        SDL_DestroyTexture(texture_menu);

    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);

    if(window != NULL)
        SDL_DestroyWindow(window);
 
    Mix_CloseAudio();
    SDL_Quit();

    return statut;
}