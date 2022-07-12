#include "constante.h"
#include "appel.h"

//gcc .\src\*.c -o .\bin\bomberman -I include -L .\lib\ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lpthread

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
    int debut = 0;
    int music_changement = 0, rejouer = 0;

    memset(&in, SDL_FALSE, sizeof(Input));

    if(init(&window, &renderer, LARGEUR_WINDOW, HAUTEUR_WINDOW) != 0)
        goto quit;

    music = Mix_LoadMUS("src/musiques/intro_musique_menu.mp3");
    printf("LOAD_MUSIC : src/musiques/intro_musique_menu.mp3\n");
    if(music == NULL)
    {
        SDL_Log("ERREUR : LOAD_MUS > %s\n", Mix_GetError());
        goto quit;
    }

    texture_menu = load_image("src/images/menu.jpg", renderer);
    if(texture_menu == NULL)
        goto quit;

    printf("PLAY_MUSIC\n");
    if(Mix_PlayMusic(music, 1) != 0)
    {
        SDL_Log("ERREUR : PLAY_MUSIC > %s\n", Mix_GetError());
        goto quit;
    }
    
    while(!in.quit)
    {
        frame_limit = SDL_GetTicks() + FPS;

        if(change_music(debut, 35168, &music_changement, "src/musiques/musique_menu.mp3", music, 0) == -1)
            goto quit;

        if(SDL_RenderCopy(renderer, texture_menu, NULL, NULL) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n", SDL_GetError());
            goto quit;
        }

        SDL_RenderPresent(renderer);

        update_event(&in);

        if(in.mouse[SDL_BUTTON_LEFT] && in.x >= 1400 && in.x <= 1820)
        {
            if(in.y >= 86 && in.y <= 233)
            {
                Mix_FreeMusic(music);
                SDL_DestroyTexture(texture_menu);

                if(!play(renderer, &in))
                    goto quit;
                
                else if(in.quit == 2)   
                    in.quit = SDL_FALSE;

                music_changement = 0;
                debut = SDL_GetTicks();

                music = Mix_LoadMUS("src/musiques/intro_musique_menu.mp3");
                if(music == NULL)
                {
                    SDL_Log("ERREUR : LOAD_MUS > %s\n", Mix_GetError());
                    goto quit;
                }

                if(Mix_PlayMusic(music, -1) != 0)
                {
                    SDL_Log("ERREUR : PLAY_MUSIC > %s\n", Mix_GetError());
                    goto quit;
                }

                Mix_VolumeMusic(MIX_MAX_VOLUME);

                texture_menu = load_image("src/images/menu.jpg", renderer);
                if(texture_menu == NULL)
                    goto quit;
            }

            else if(in.y >= 296 && in.y <= 443)
                in.quit = SDL_TRUE;
        }

        limite_fps(frame_limit, FPS);
    }

    statut = EXIT_SUCCESS;

    quit:

    if(music != NULL)
    {
        Mix_FreeMusic(music);
        printf("FREE_MUSIC\n");
    }

    if(texture_menu != NULL) 
    {   
        SDL_DestroyTexture(texture_menu);
        printf("DESTROY_TEXTURE : TEXTURE_MENU\n");
    }

    if(renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
        printf("DESTROY_RENDERER : RENDERER\n");
    }

    if(window != NULL)
    {
        SDL_DestroyWindow(window);
        printf("DESTROY_WINDOW : WINDOW\n");
    }
 
    Mix_CloseAudio();
    printf("CLOSE_AUDIO\n");
    SDL_Quit();
    printf("QUIT\n");

    return statut;
}