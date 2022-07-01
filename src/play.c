#include "constante.h"
#include "appel.h"

SDL_Rect mur = {885, 465, 1035, 615};

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

void deplacer_joueur(Link *link, const int direction, Input *in)
{
    link->direction_actuel = link->direction[direction];
    link->forme[direction].x = link->forme_actuel.x;
    link->forme[direction].y = link->forme_actuel.y;
    link->forme_actuel = link->forme[direction];

    
    
    

    if(direction == haut && link->forme_actuel.y > 0)
        link->forme_actuel.y--;

    if(direction == bas && (link->forme_actuel.y + link->forme_actuel.h) < HAUTEUR)
        link->forme_actuel.y++;

    if(link->colision == gauche && (direction == haut || direction == bas))   
    {
        link->forme_actuel.x += 5;
        in->key[SDL_SCANCODE_A] = SDL_FALSE;
    }
    else if(direction == gauche && link->forme_actuel.x > 0)
    {
        link->forme_actuel.x--;
        link->colision = -1;
    }

    if(link->colision == droite && (direction == haut || direction == bas))
    {
        link->forme_actuel.x -= 5;
        in->key[SDL_SCANCODE_D] = SDL_FALSE;
    }
    else if(direction == droite && (link->forme_actuel.x + link->forme_actuel.w) < LARGEUR)
    {
        link->forme_actuel.x++;
        link->colision = -1;
    }

    if(SDL_HasIntersection(&link->forme_actuel, &mur))
    {
        if(direction == haut && link->forme_actuel.y > 0)
            link->forme_actuel.y++;

        if(direction == bas && (link->forme_actuel.y + link->forme_actuel.h) < HAUTEUR)
            link->forme_actuel.y--;

        if(direction == gauche && link->forme_actuel.x > 0)
            link->forme_actuel.x++;

        if(direction == droite && (link->forme_actuel.x + link->forme_actuel.w) < LARGEUR)
            link->forme_actuel.x--;

        link->colision = direction;
    }
}   

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int play(SDL_Renderer *renderer, Input *in)
{
    SDL_Event event;
    SDL_bool game_launched = SDL_TRUE;
    SDL_Texture *texture_arriere_plan = NULL, *texture_mur = NULL;
    Link link;
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

        if(SDL_RenderCopy(renderer, texture_mur, NULL, &mur) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
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
            deplacer_joueur(&link, haut, in);
        
        if(in->key[SDL_SCANCODE_S])
            deplacer_joueur(&link, bas, in);

        if(in->key[SDL_SCANCODE_A])
            deplacer_joueur(&link, gauche, in);

        if(in->key[SDL_SCANCODE_D])
            deplacer_joueur(&link, droite, in);

        limite_fps(frame_limit, 1);
    } 

    destroy_play(texture_arriere_plan, &link, texture_mur);
                
    return 0;
}