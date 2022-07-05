#include "constante.h"
#include "appel.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void destroy_play(SDL_Texture *texture_arriere_plan, Link *link, SDL_Texture *texture_mur, Mix_Music *music)
{
    if(music != NULL)   
        Mix_FreeMusic(music);

    if(link->direction_actuel != NULL)
    {
        SDL_DestroyTexture(link->direction_actuel);
        free_link(link->direction);
    }

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
    SDL_Texture *texture_arriere_plan = NULL, *texture_mur_destructible = NULL;
    int debut = SDL_GetTicks();
    Mix_Music *music;
    Link link;
    Map map[LARGEUR][HAUTEUR];
    unsigned int frame_limit = 0; 
    int music_changement = 0;

    create_map(map);

    music = music = Mix_LoadMUS("src/musiques/intro_musique_jeu.mp3");
    if(music == NULL)
    {
        SDL_Log("ERREUR : LOAD_MUS > %s\n", Mix_GetError());
        return 1;
    }

    texture_arriere_plan = load_image("src/images/map.jpg", renderer);
    if(texture_arriere_plan == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n", SDL_GetError());
        Mix_FreeMusic(music);
        return 1;
    }

    texture_mur_destructible = load_image("src/images/mur_destructible.png", renderer);
    if(texture_mur_destructible == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n", SDL_GetError());
        destroy_play(texture_arriere_plan, NULL, texture_mur_destructible, music);
        return 1;
    }

    if(SDL_QueryTexture(texture_arriere_plan, NULL, NULL, NULL, NULL) != 0)
    {
        SDL_Log("ERREUR : QUERY_TEXTURE > %s\n",SDL_GetError());
        destroy_play(texture_arriere_plan, NULL, texture_mur_destructible, music);
        return 1;
    }

    if(create_link(&link, renderer) != 0)
    {
        destroy_play(texture_arriere_plan, NULL, texture_mur_destructible, music);
        return 1;
    }

    if(Mix_PlayMusic(music, 1) != 0)
    {
        SDL_Log("ERREUR : PLAY_MUSIC > %s\n", Mix_GetError());
        destroy_play(texture_arriere_plan, NULL, texture_mur_destructible, music);
        return 1;
    }

    Mix_VolumeMusic(MIX_MAX_VOLUME / 3);

    while (!in->quit && !in->key[SDL_SCANCODE_ESCAPE])
    {
        frame_limit = SDL_GetTicks() + FPS;

        if(change_music(debut, 15074, &music_changement, "src/musiques/musique_jeu.mp3", music) == -1)
        {
            destroy_play(texture_arriere_plan, NULL, texture_mur_destructible, music);
            return 1;
        }

        if(SDL_RenderClear(renderer) != 0)
        {
            SDL_Log("ERREUR : QUERY_TEXTURE > %s\n",SDL_GetError());
            destroy_play(texture_arriere_plan, &link, texture_mur_destructible, music);
            return 1;
        }

        if(SDL_QueryTexture(link.direction_actuel, NULL, NULL, &link.forme.w, &link.forme.h) != 0)
        {
            SDL_Log("ERREUR : QUERY_TEXTURE > %s\n",SDL_GetError());
            destroy_play(texture_arriere_plan, &link, texture_mur_destructible, music);
            return 1;
        }

        if(SDL_RenderCopy(renderer, texture_arriere_plan, NULL, NULL) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            destroy_play(texture_arriere_plan, &link, texture_mur_destructible, music);
            return 1;
        }

        if(!print_wall(map, renderer, texture_mur_destructible))
        {
            destroy_play(texture_arriere_plan, &link, texture_mur_destructible, music);
            return 1;
        }

        if(SDL_RenderCopy(renderer, link.direction_actuel, NULL, &link.forme) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            destroy_play(texture_arriere_plan, &link, texture_mur_destructible, music);
            return 1;
        }

        SDL_RenderPresent(renderer);

        update_event(in);

        if(in->key[SDL_SCANCODE_W])   
        {
            deplacer_joueur(&link, HAUT);
            detecte_map(map, &link, HAUT);
        }

        if(in->key[SDL_SCANCODE_S])
        {
            deplacer_joueur(&link, BAS);
            detecte_map(map, &link, BAS);
        }

        if(in->key[SDL_SCANCODE_A])
        {
            deplacer_joueur(&link, GAUCHE);
            detecte_map(map, &link, GAUCHE);
        }

        if(in->key[SDL_SCANCODE_D])
        {
            deplacer_joueur(&link, DROITE);
            detecte_map(map, &link, DROITE);
        }

        limite_fps(frame_limit, 1); 
    } 

    destroy_play(texture_arriere_plan, &link, texture_mur_destructible, music);
                
    return 0;
}