#include "constante.h"
#include "appel.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void destroy_play(SDL_Texture *texture_arriere_plan, Link *link)
{
    SDL_DestroyTexture(texture_arriere_plan);
    SDL_DestroyTexture(link->direction_actuel);
    free_link(link->direction);
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void deplacer_joueur(Link *link, const int direction)
{
    if(link->deplacement != direction)
    {
        link->direction_actuel = link->direction[direction];
        link->forme[direction].x = link->forme_actuel.x;
        link->forme[direction].y = link->forme_actuel.y;
        link->forme_actuel = link->forme[direction];
    }

    if(direction == haut && link->forme_actuel.y > 0 )
    {
        link->forme_actuel.y--;
        link->deplacement = haut;
    }

    if(direction == bas && (link->forme_actuel.y + link->forme_actuel.h) < HAUTEUR)
    {
        link->forme_actuel.y++;
        link->deplacement = bas;
    }

    if(direction == gauche && link->forme_actuel.x > 0)
    {
        link->forme_actuel.x--;
        link->deplacement = gauche;
    }

    if(direction == droite && (link->forme_actuel.x + link->forme_actuel.w) < LARGEUR)
    {
        link->forme_actuel.x++;
        link->deplacement = droite;
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int play(SDL_Renderer *renderer, Input *in)
{
    SDL_Event event;
    SDL_bool game_launched = SDL_TRUE;
    SDL_Texture *texture_arriere_plan = NULL;
    Link link;
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

    if(create_link(&link, renderer) != 0)
    {
        SDL_DestroyTexture(texture_arriere_plan);
        return 1;
    }

    link.direction_actuel = link.direction[bas];
    link.forme_actuel = link.forme[bas];
    link.deplacement = bas;

    if(SDL_QueryTexture(link.direction_actuel, NULL, NULL, &link.forme_actuel.w, &link.forme_actuel.h) != 0)
    {
        SDL_Log("ERREUR : QUERY_TEXTURE > %s\n",SDL_GetError());
        destroy_play(texture_arriere_plan, &link);
        return 1;
    }

    while (!in->quit && !in->key[SDL_SCANCODE_ESCAPE])
    {
        frame_limit = SDL_GetTicks() + FPS;
        SDL_RenderClear(renderer);

        if(SDL_RenderCopy(renderer, texture_arriere_plan, NULL, NULL) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            destroy_play(texture_arriere_plan, &link);
            return 1;
        }

        if(SDL_RenderCopy(renderer, link.direction_actuel, NULL, &link.forme_actuel) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            destroy_play(texture_arriere_plan, &link);
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

    destroy_play(texture_arriere_plan, &link);
                
    return 0;
}