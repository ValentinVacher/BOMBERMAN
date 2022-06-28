#include "source.h"

void clean_resources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t)
{
    if(t != NULL)
        SDL_DestroyTexture(t);

    if(r != NULL)
        SDL_DestroyRenderer(r);
    
    if(w != NULL)
        SDL_DestroyWindow(w);

    SDL_Quit();
}

/*---------------------------------------------------------------------------------*/

int play(SDL_Renderer *renderer, SDL_Rect taille_renderer)
{
    SDL_Event event;
    SDL_bool game_launched = SDL_TRUE;
    SDL_Surface *blanc;
    SDL_Texture *texture = NULL;

    SDL_RenderClear(renderer);

    blanc = SDL_CreateRGBSurface(0, LARGEUR, HAUTEUR, 32, 0, 0, 0, 0);

    if(SDL_FillRect(blanc, NULL, SDL_MapRGB(blanc->format, 255, 255, 255)) != 0)
    {
        printf("SDL_FillRect\n");
        SDL_Log("ERREUr > %s\n", SDL_GetError());
        return 1;
    }

    texture = SDL_CreateTextureFromSurface(renderer, blanc);
    SDL_FreeSurface(blanc);
    if(texture == NULL)
    {
        printf("SDL_CreateTextureFromSurface\n");
        SDL_Log("ERREUr > %s\n", SDL_GetError());
        return 1;
    }


    if(SDL_QueryTexture(texture, NULL, NULL, &taille_renderer.w, &taille_renderer.h) != 0)
    {
        printf("SDL_QueryTexture\n");
        SDL_Log("ERREUR > %s\n",SDL_GetError());
        SDL_DestroyTexture(texture);
        return 1;
    }

    while (game_launched)
    {
        if(SDL_RenderCopy(renderer, texture, NULL, &taille_renderer) != 0)
        {
            printf("SDL_RenderCopy\n");
            SDL_Log("ERREUR > %s\n",SDL_GetError());
            SDL_DestroyTexture(texture);
            return 1;
        }

        SDL_RenderPresent(renderer);

        while(SDL_PollEvent(&event) == 1)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                game_launched = SDL_FALSE;
                return 1;
            
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    game_launched = SDL_FALSE;
                    break;
                
                default:
                    break;
                }
            
            default:
                break;
            }
        }
    } 
    return 0;
}