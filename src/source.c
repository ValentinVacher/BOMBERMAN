#include "source.h"

void clean_resources(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture_menu, SDL_Texture *texture_bouton_quitter)
{
    if(texture_bouton_quitter != NULL)
        SDL_DestroyTexture(texture_bouton_quitter);
        
    if(texture_menu != NULL)
        SDL_DestroyTexture(texture_menu);

    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    
    if(window != NULL)
        SDL_DestroyWindow(window);

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

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, LARGEUR, HAUTEUR);
    if(texture == NULL)
    {
        SDL_Log("ERREUr > %s\n", SDL_GetError());
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderFillRect(renderer, NULL);
    SDL_SetRenderTarget(renderer, NULL);

    if(SDL_QueryTexture(texture, NULL, NULL, &taille_renderer.w, &taille_renderer.h) != 0)
    {
        SDL_Log("ERREUR > %s\n",SDL_GetError());
        SDL_DestroyTexture(texture);
        return 1;
    }

    while (game_launched)
    {
        if(SDL_RenderCopy(renderer, texture, NULL, &taille_renderer) != 0)
        {
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