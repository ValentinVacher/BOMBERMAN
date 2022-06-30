#include "source.h"

void destroy_play(SDL_Texture *texture_arriere_plan, SDL_Texture *link_actuel, SDL_Texture *link[])
{
    SDL_DestroyTexture(texture_arriere_plan);
    SDL_DestroyTexture(link_actuel);
    free_link(link);
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void deplacer_joueur(SDL_Rect *position_link, const int direction)
{
    if(direction == haut)
        position_link->y--;

    if(direction == bas)
        position_link->y++;

    if(direction == gauche)
        position_link->x--;

    if(direction == droite)
        position_link->x++;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int play(SDL_Renderer *renderer, input *in)
{
    SDL_Event event;
    SDL_bool game_launched = SDL_TRUE;
    SDL_Texture *texture_arriere_plan = NULL, *link[4], *link_actuel = NULL;
    SDL_Rect taille_link_actuel, taille_link[4];
    unsigned int frame_limit = 0;

    texture_arriere_plan = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, LARGEUR, HAUTEUR);
    if(texture_arriere_plan == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n", SDL_GetError());
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_SetRenderTarget(renderer, texture_arriere_plan);
    SDL_RenderFillRect(renderer, NULL);
    SDL_SetRenderTarget(renderer, NULL);

    if(SDL_QueryTexture(texture_arriere_plan, NULL, NULL, NULL, NULL) != 0)
    {
        SDL_Log("ERREUR : QUERY_TEXTURE > %s\n",SDL_GetError());
        SDL_DestroyTexture(texture_arriere_plan);
        return 1;
    }

    if(create_link(link, renderer, taille_link) != 0)
    {
        SDL_DestroyTexture(texture_arriere_plan);
        return 1;
    }

    link_actuel = link[bas];
    taille_link_actuel = taille_link[bas];

    if(SDL_QueryTexture(link_actuel, NULL, NULL, &taille_link_actuel.w, &taille_link_actuel.h) != 0)
    {
        SDL_Log("ERREUR : QUERY_TEXTURE > %s\n",SDL_GetError());
        destroy_play(texture_arriere_plan, link_actuel, link);
        return 1;
    }

    while (!in->quit)
    {
        frame_limit = SDL_GetTicks() + FPS;
        SDL_RenderClear(renderer);

        if(SDL_RenderCopy(renderer, texture_arriere_plan, NULL, NULL) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            destroy_play(texture_arriere_plan, link_actuel, link);
            return 1;
        }

        if(SDL_RenderCopy(renderer, link_actuel, NULL, &taille_link_actuel) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            destroy_play(texture_arriere_plan, link_actuel, link);
            return 1;
        }

        SDL_RenderPresent(renderer);

        update_event(in);

        if(in->key[SDL_SCANCODE_W])
            deplacer_joueur(&taille_link_actuel, haut);
        
        if(in->key[SDL_SCANCODE_S])
            deplacer_joueur(&taille_link_actuel, bas);

        if(in->key[SDL_SCANCODE_A])
            deplacer_joueur(&taille_link_actuel, gauche);

        if(in->key[SDL_SCANCODE_D])
            deplacer_joueur(&taille_link_actuel, droite);

        if(in->key[SDL_SCANCODE_ESCAPE])
            break;

        limite_fps(frame_limit);
    } 

    destroy_play(texture_arriere_plan, link_actuel, link);
                
    return 0;
}