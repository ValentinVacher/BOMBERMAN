#include "constante.h"
#include "appel.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void destroy_play(SDL_Texture *texture_arriere_plan, Link *link, SDL_Texture *texture_mur)
{
    if(link->direction_actuel != NULL)
        SDL_DestroyTexture(link->direction_actuel);
        free_link(link->direction);

    if(texture_mur != NULL)
        SDL_DestroyTexture(texture_mur);

    if(texture_arriere_plan != NULL)
        SDL_DestroyTexture(texture_arriere_plan);
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int play(SDL_Renderer *renderer, Input *in)
{
    SDL_Event event;
    SDL_bool game_launched = SDL_TRUE;
    SDL_Texture *texture_arriere_plan = NULL, *texture_mur = NULL;
    Link link;
    Map map[LARGEUR / 150][HAUTEUR / 150];
    SDL_Rect mur = {0, 0, 150, 150};
    unsigned int frame_limit = 0;   



    texture_arriere_plan = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, LARGEUR, HAUTEUR);
    if(texture_arriere_plan == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n", SDL_GetError());
        return 1;
    }

    texture_mur = load_image("src/images/mur.png", renderer);
    if(texture_mur == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n", SDL_GetError());
        destroy_play(texture_arriere_plan, NULL, texture_mur);
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_SetRenderTarget(renderer, texture_arriere_plan);
    SDL_RenderFillRect(renderer, NULL);
    SDL_SetRenderTarget(renderer, NULL);

    if(SDL_QueryTexture(texture_arriere_plan, NULL, NULL, NULL, NULL) != 0)
    {
        SDL_Log("ERREUR : QUERY_TEXTURE > %s\n",SDL_GetError());
        destroy_play(texture_arriere_plan, NULL, texture_mur);
        return 1;
    }

    if(SDL_QueryTexture(texture_mur, NULL, NULL, &mur.w, &mur.h))
    {
        SDL_Log("ERREUR : QUERY_TEXTURE > %s\n",SDL_GetError());
        destroy_play(texture_arriere_plan, NULL, texture_mur);
        return 1;
    }

    if(create_link(&link, renderer) != 0)
    {
        destroy_play(texture_arriere_plan, NULL, texture_mur);
        return 1;
    }

    link.direction_actuel = link.direction[bas];

    while (!in->quit && !in->key[SDL_SCANCODE_ESCAPE])
    {
        frame_limit = SDL_GetTicks() + FPS;
        SDL_RenderClear(renderer);

        if(SDL_QueryTexture(link.direction_actuel, NULL, NULL, &link.forme.w, &link.forme.h) != 0)
        {
            SDL_Log("ERREUR : QUERY_TEXTURE > %s\n",SDL_GetError());
            destroy_play(texture_arriere_plan, &link, texture_mur);
            return 1;
        }

        if(SDL_RenderCopy(renderer, texture_arriere_plan, NULL, NULL) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            destroy_play(texture_arriere_plan, &link, texture_mur);
            return 1;
        }

        if(!create_map(renderer, texture_mur, map))
        {
            destroy_play(texture_arriere_plan, &link, texture_mur);
            return 1;
        }

        if(SDL_RenderCopy(renderer, link.direction_actuel, NULL, &link.forme) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            destroy_play(texture_arriere_plan, &link, texture_mur);
            return 1;
        }

        SDL_RenderPresent(renderer);

        update_event(in);

        if(in->key[SDL_SCANCODE_W])   
            deplacer_joueur(&link, haut);
        
        if(in->key[SDL_SCANCODE_S])
            deplacer_joueur(&link, bas);

        if(in->key[SDL_SCANCODE_A])
            deplacer_joueur(&link, gauche);

        if(in->key[SDL_SCANCODE_D])
            deplacer_joueur(&link, droite);

        limite_fps(frame_limit, 1);
    } 

    /*int i, j;

    for(i = 0 ; i < LARGEUR / 150 ; i++)
    {
        for(j = 0 ; j < HAUTEUR / 150 ; j++)
        {
            printf("map[%d][%d] = %d\n", i, j, map[i][j]);
        }
    }*/

    destroy_play(texture_arriere_plan, &link, texture_mur);
                
    return 0;
}