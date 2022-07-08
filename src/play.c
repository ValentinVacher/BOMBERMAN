#include "constante.h"
#include "appel.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

SDL_bool play(SDL_Renderer *renderer, Input *in)
{

/*--------------------------------------------------------------------------------------------------------------------------------*/

    SDL_Event event;
    SDL_bool game_launched = SDL_TRUE, space = SDL_FALSE, rctrl = SDL_FALSE, exite = SDL_FALSE;
    SDL_Texture *texture_arriere_plan = NULL, *texture_mur_destructible = NULL, *texture_bombe = NULL, *texture_explosion = NULL;
    int debut = SDL_GetTicks(), music_changement = 0;
    Mix_Music *music;
    Link link, link_rouge;
    Map map[LARGEUR][HAUTEUR];
    unsigned int frame_limit = 0; 
    pthread_t thread[2];

/*--------------------------------------------------------------------------------------------------------------------------------*/

    create_map(map);

    music = music = Mix_LoadMUS("src/musiques/intro_musique_jeu.mp3");
    if(music == NULL)
    {
        SDL_Log("ERREUR : LOAD_MUS > %s\n", Mix_GetError());
        return exite;
    }

    texture_arriere_plan = load_image("src/images/map.jpg", renderer);
    if(texture_arriere_plan == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n", SDL_GetError());
        goto quit;
    }

    texture_mur_destructible = load_image("src/images/mur_destructible.png", renderer);
    if(texture_mur_destructible == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n", SDL_GetError());
        goto quit;
    }

    texture_bombe = load_image("src/images/bombe.png", renderer);
    if(texture_bombe == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n", SDL_GetError());
        goto quit;
    }

    texture_explosion = load_image("src/images/explosion.png", renderer);
    if(texture_bombe == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n", SDL_GetError());
        goto quit;
    }

    if(SDL_QueryTexture(texture_arriere_plan, NULL, NULL, NULL, NULL) != 0)
    {
        SDL_Log("ERREUR : QUERY_TEXTURE > %s\n",SDL_GetError());
        goto quit;
    }

    if(!create_link(&link, renderer, LINK))
        goto quit;

    if(!create_link(&link_rouge, renderer, LINK_ROUGE))
        goto quit;

    if(Mix_PlayMusic(music, 1) != 0)
    {
        SDL_Log("ERREUR : PLAY_MUSIC > %s\n", Mix_GetError());
        goto quit;
    }

    Mix_VolumeMusic(MIX_MAX_VOLUME / 3);

/*--------------------------------------------------------------------------------------------------------------------------------*/

    while (!in->quit && !in->key[SDL_SCANCODE_ESCAPE])
    {
        frame_limit = SDL_GetTicks() + FPS;

        if(change_music(debut, 15074, &music_changement, "src/musiques/musique_jeu.mp3", music) == -1)
            goto quit;

        if(SDL_RenderClear(renderer) != 0)
        {
            SDL_Log("ERREUR : QUERY_TEXTURE > %s\n",SDL_GetError());
            goto quit;
        }

        if(SDL_QueryTexture(link.direction_actuel, NULL, NULL, &link.forme.w, &link.forme.h) != 0)
        {
            SDL_Log("ERREUR : QUERY_TEXTURE > %s\n",SDL_GetError());
            goto quit;
        }

        if(SDL_QueryTexture(link_rouge.direction_actuel, NULL, NULL, &link_rouge.forme.w, &link_rouge.forme.h) != 0)
        {
            SDL_Log("ERREUR : QUERY_TEXTURE > %s\n",SDL_GetError());
            goto quit;
        }

        if(SDL_RenderCopy(renderer, texture_arriere_plan, NULL, NULL) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            goto quit;
        }

        if(!print_wall(map, renderer, texture_mur_destructible))
            goto quit;

        if(!pose_bombe(texture_bombe, renderer, &link, map, texture_explosion))
            goto quit;

        if(!pose_bombe(texture_bombe, renderer, &link_rouge, map, texture_explosion))
            goto quit;

        if(SDL_RenderCopy(renderer, link.direction_actuel, NULL, &link.forme) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            goto quit;
        }

        if(SDL_RenderCopy(renderer, link_rouge.direction_actuel, NULL, &link_rouge.forme) != 0)
        {
            SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
            goto quit;
        }

        SDL_RenderPresent(renderer);

/*--------------------------------------------------------------------------------------------------------------------------------*/

        update_event(in);

        if(in->key[SDL_SCANCODE_W])   
        {
            deplacer_joueur(&link, HAUT);
            detecte_map(map, &link, HAUT, LINK);
        }

        if(in->key[SDL_SCANCODE_S])
        {
            deplacer_joueur(&link, BAS);
            detecte_map(map, &link, BAS, LINK);
        }

        if(in->key[SDL_SCANCODE_A])
        {
            deplacer_joueur(&link, GAUCHE);
            detecte_map(map, &link, GAUCHE, LINK);
        }

        if(in->key[SDL_SCANCODE_D])
        {
            deplacer_joueur(&link, DROITE);
            detecte_map(map, &link, DROITE, LINK);
        }

        if(in->key[SDL_SCANCODE_SPACE] && !space)
        {
            creation_bombe(&link, &thread[0]);
            space = SDL_TRUE;
        }

        else if(!in->key[SDL_SCANCODE_SPACE] && space)
            space = SDL_FALSE;

/*--------------------------------------------------------------------------------------------------------------------------------*/

        if(in->key[SDL_SCANCODE_UP])   
        {
            deplacer_joueur(&link_rouge, HAUT);
            detecte_map(map, &link_rouge, HAUT, LINK_ROUGE);
        }

        if(in->key[SDL_SCANCODE_DOWN])
        {
            deplacer_joueur(&link_rouge, BAS);
            detecte_map(map, &link_rouge, BAS, LINK_ROUGE);
        }

        if(in->key[SDL_SCANCODE_LEFT])
        {
            deplacer_joueur(&link_rouge, GAUCHE);
            detecte_map(map, &link_rouge, GAUCHE, LINK_ROUGE);
        }

        if(in->key[SDL_SCANCODE_RIGHT])
        {
            deplacer_joueur(&link_rouge, DROITE);
            detecte_map(map, &link_rouge, DROITE, LINK_ROUGE);
        }

        if(in->key[SDL_SCANCODE_RCTRL] && !rctrl)
        {
            creation_bombe(&link_rouge, &thread[1]);
            rctrl = SDL_TRUE;
        }

        else if(!in->key[SDL_SCANCODE_RCTRL] && rctrl)
            rctrl = SDL_FALSE;

        limite_fps(frame_limit, 1); 
    } 

/*--------------------------------------------------------------------------------------------------------------------------------*/

    exite = SDL_TRUE;

    quit:

    if(music != NULL)   
        Mix_FreeMusic(music);

    if(link.direction_actuel != NULL)
    {
        SDL_DestroyTexture(link.direction_actuel);
        free_link(link.direction);
    }

    if(link_rouge.direction_actuel != NULL)
    {
        SDL_DestroyTexture(link_rouge.direction_actuel);
        free_link(link_rouge.direction);
    }
    
    if(texture_explosion != NULL)
        SDL_DestroyTexture(texture_explosion);

    if(texture_bombe != NULL)
        SDL_DestroyTexture(texture_bombe);

    if(texture_mur_destructible != NULL)
        SDL_DestroyTexture(texture_mur_destructible);

    if(texture_arriere_plan != NULL)
        SDL_DestroyTexture(texture_arriere_plan);

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
                
    return exite;
}