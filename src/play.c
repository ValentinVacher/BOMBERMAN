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
    int nb_mur = 4;
    SDL_Rect mur[nb_mur];
    unsigned int frame_limit = 0;   

    mur[0].x = 565;
    mur[0].y = 285;
    mur[0].w = 150;
    mur[0].h = 150;

    mur[1].x = 1205;
    mur[1].y = 285;
    mur[1].w = 150;
    mur[1].h = 150;

    mur[2].x = 565;
    mur[2].y = 645;
    mur[2].w = 150;
    mur[2].h = 150;

    mur[3].x = 1205;
    mur[3].y = 645;
    mur[3].w = 150;
    mur[3].h = 150;

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

    if(SDL_QueryTexture(texture_mur, NULL, NULL, &mur[0].w, &mur[0].h))
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
    link.forme_actuel = link.forme[bas];

    while (!in->quit && !in->key[SDL_SCANCODE_ESCAPE])
    {
        frame_limit = SDL_GetTicks() + FPS;
        SDL_RenderClear(renderer);

        if(SDL_QueryTexture(link.direction_actuel, NULL, NULL, &link.forme_actuel.w, &link.forme_actuel.h) != 0)
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

        if(!print_wall(mur, nb_mur, renderer, texture_mur))
        {
            destroy_play(texture_arriere_plan, &link, texture_mur);
            return 1;
        }

        if(SDL_RenderCopy(renderer, link.direction_actuel, NULL, &link.forme_actuel) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            destroy_play(texture_arriere_plan, &link, texture_mur);
            return 1;
        }

        SDL_RenderPresent(renderer);

        update_event(in);

        if(in->key[SDL_SCANCODE_W])   
            deplacer_joueur(&link, haut, mur, nb_mur);
        
        if(in->key[SDL_SCANCODE_S])
            deplacer_joueur(&link, bas, mur, nb_mur);

        if(in->key[SDL_SCANCODE_A])
            deplacer_joueur(&link, gauche, mur, nb_mur);

        if(in->key[SDL_SCANCODE_D])
            deplacer_joueur(&link, droite, mur, nb_mur);

        limite_fps(frame_limit, 1);
    } 

    destroy_play(texture_arriere_plan, &link, texture_mur);
                
    return 0;
}