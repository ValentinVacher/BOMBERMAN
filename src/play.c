#include "constante.h"
#include "appel.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

SDL_bool play(SDL_Renderer *renderer, Input *in)
{

/*--------------------------------------------------------------------------------------------------------------------------------*/

    SDL_Event event;
    SDL_bool game_launched = SDL_TRUE, space = SDL_FALSE, rctrl = SDL_FALSE, exite_statue = SDL_FALSE;
    SDL_Texture *texture_arriere_plan = NULL, *texture_mur_destructible = NULL, *texture_bombe[3], *texture_victoire[2];
    int debut = SDL_GetTicks(), music_changement = 0, i = 0, victoire = 0,  rejouer = 1, direction = BAS;
    Mix_Music *music;
    Mix_Chunk *explosion;
    Link link, link_rouge;
    Map map[LARGEUR][HAUTEUR];
    unsigned int frame_limit = 0; 
    pthread_t thread[3];

/*--------------------------------------------------------------------------------------------------------------------------------*/

    Mix_AllocateChannels(2);

    explosion = Mix_LoadWAV("src/musiques/explosion.mp3");
    printf("LOAD_WAV : src/musiques/explosion.mp3\n");
    if(explosion == NULL)
    {
        SDL_Log("ERREUR : LOAD_MUS > %s\n", Mix_GetError());
        goto quit_play;
    }

    Mix_VolumeChunk(explosion, MIX_MAX_VOLUME / 2);

    texture_arriere_plan = load_image("src/images/map.jpg", renderer);
    if(texture_arriere_plan == NULL)
        goto quit_play;

    texture_mur_destructible = load_image("src/images/mur_destructible.png", renderer);
    if(texture_mur_destructible == NULL)
        goto quit_play;

    texture_bombe[0] = load_image("src/images/bombe.png", renderer);
    if(texture_bombe[0] == NULL)
        goto quit_play;

    texture_bombe[1] = load_image("src/images/explosion.png", renderer);
    if(texture_bombe[1] == NULL)
        goto quit_play;

    texture_bombe[2] = load_image("src/images/bombe_rouge.png", renderer);
    if(texture_bombe[2] == NULL)
        goto quit_play;

    texture_victoire[0] = load_image("src/images/victoire_link_vert.png", renderer);
    if(texture_arriere_plan == NULL)
        goto quit_play;

    texture_victoire[1] = load_image("src/images/victoire_link_rouge.png", renderer);
    if(texture_arriere_plan == NULL)
        goto quit_play;

/*--------------------------------------------------------------------------------------------------------------------------------*/

    while(rejouer && !in->quit && !in->key[SDL_SCANCODE_ESCAPE])
    {
        victoire = 0;
        debut = SDL_GetTicks();
        music_changement = 0;

        create_map(map);

        music = Mix_LoadMUS("src/musiques/intro_musique_jeu.mp3");
        printf("LOAD_MUSIC : src/musiques/intro_musique_jeu.mp3\n");
        if(music == NULL)
        {
            SDL_Log("ERREUR : LOAD_MUS > %s\n", Mix_GetError());
            goto quit_play;
        }

        if(!create_link(&link, renderer, LINK))
            goto quit_play;

        if(!create_link(&link_rouge, renderer, LINK_ROUGE))
            goto quit_play;

        printf("PLAY_MUSIC\n");
        if(Mix_PlayMusic(music, 1) != 0)
        {
            SDL_Log("ERREUR : PLAY_MUSIC > %s\n", Mix_GetError());
            goto quit_play;
        }

        Mix_VolumeMusic(MIX_MAX_VOLUME / 3);

/*--------------------------------------------------------------------------------------------------------------------------------*/

        while (!in->quit && !in->key[SDL_SCANCODE_ESCAPE])
        {
            frame_limit = SDL_GetTicks() + FPS;

            if(change_music(debut, 15074, &music_changement, "src/musiques/musique_jeu.mp3", music, 0) == -1)
                goto quit_play;

            if(victoire != 0)
            {
                if(music_changement <= 1)
                {
                    debut =SDL_GetTicks();

                    music = Mix_LoadMUS("src/musiques/intro_musique_victoire.mp3");
                    if(music == NULL)
                    {
                        SDL_Log("ERREUR : LOAD_MUS > %s\n", Mix_GetError());
                        goto quit_play;
                    }

                    if(Mix_PlayMusic(music, 1) != 0)
                    {
                        SDL_Log("ERREUR : PLAY_MUSIC > %s\n", Mix_GetError());
                        goto quit_play;
                    }

                    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

                    music_changement++;
                }

                else if(change_music(debut, 8103, &music_changement, "src/musiques/musique_victoire.mp3", music, 2))
                    goto quit_play;
            }

            if(SDL_RenderClear(renderer) != 0)
            {
                SDL_Log("ERREUR : RENDER_CLEAR > %s\n",SDL_GetError());
                goto quit_play;
            }

            if(SDL_QueryTexture(link.direction_actuel, NULL, NULL, &link.forme.w, &link.forme.h) != 0)
            {
                SDL_Log("ERREUR QUERY_TEXTURE : LINK.DIRECTION_ACTUEL > %s\n",SDL_GetError());
                goto quit_play;
            }

            if(SDL_QueryTexture(link_rouge.direction_actuel, NULL, NULL, &link_rouge.forme.w, &link_rouge.forme.h) != 0)
            {
                SDL_Log("ERREUR QUERY_TEXTURE : LINK_ROUGE.DIRECTION_ACTUEL > %s\n",SDL_GetError());
                goto quit_play;
            }

            if(SDL_RenderCopy(renderer, texture_arriere_plan, NULL, NULL) != 0)
            {
                SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
                goto quit_play;
            }

            if(!print_wall(map, renderer, texture_mur_destructible))
                goto quit_play;

            if(!pose_bombe(texture_bombe, renderer, &link, &link_rouge ,map, explosion, &victoire))
                goto quit_play;

            if(!pose_bombe(texture_bombe, renderer, &link_rouge, &link ,map, explosion, &victoire))
                goto quit_play;

            if(SDL_RenderCopy(renderer, link.direction_actuel, NULL, &link.forme) != 0)
            {
                SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
                goto quit_play;
            }

            if(SDL_RenderCopy(renderer, link_rouge.direction_actuel, NULL, &link_rouge.forme) != 0)
            {
                SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
                goto quit_play;
            }

            if(victoire == LINK) 
            {   
                if(SDL_RenderCopy(renderer, texture_victoire[0], NULL, NULL))
                {
                    SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
                    goto quit_play;
                }
            }

            if(victoire == LINK_ROUGE) 
            {   
                if(SDL_RenderCopy(renderer, texture_victoire[1], NULL, NULL))
                {
                    SDL_Log("ERREUR : RENDER_COPY > %s\n",SDL_GetError());
                    goto quit_play;
                }
            }

            SDL_RenderPresent(renderer);

    /*--------------------------------------------------------------------------------------------------------------------------------*/

            update_event(in);

            if(victoire == 0)
            {
                if(in->key[SDL_SCANCODE_W])   
                {
                    deplacer_joueur(&link, HAUT);
                    detecte_map(map, &link, &link_rouge, HAUT, LINK);
                    if(!in->key[SDL_SCANCODE_A] && !in->key[SDL_SCANCODE_D] && !in->key[SDL_SCANCODE_S])
                        link_animation(&link.animation);
                    direction = HAUT;
                }

                if(in->key[SDL_SCANCODE_S])
                {
                    deplacer_joueur(&link, BAS);
                    detecte_map(map, &link, &link_rouge, BAS, LINK);
                    if(!in->key[SDL_SCANCODE_A] && !in->key[SDL_SCANCODE_D] && !in->key[SDL_SCANCODE_W])
                        link_animation(&link.animation);
                        direction = BAS;
                }

                if(in->key[SDL_SCANCODE_A])
                {
                    deplacer_joueur(&link, GAUCHE);
                    detecte_map(map, &link, &link_rouge, GAUCHE, LINK);
                    if(!in->key[SDL_SCANCODE_D])
                        link_animation(&link.animation);
                    direction = GAUCHE;
                }

                if(in->key[SDL_SCANCODE_D])
                {
                    deplacer_joueur(&link, DROITE);
                    detecte_map(map, &link, &link_rouge, DROITE, LINK);
                    if(!in->key[SDL_SCANCODE_A])
                        link_animation(&link.animation);
                        direction = DROITE;
                }

                else if(!in->key[SDL_SCANCODE_W] && !in->key[SDL_SCANCODE_S] && !in->key[SDL_SCANCODE_A] && !in->key[SDL_SCANCODE_D])
                {
                    link.animation = 0;
                    link.direction_actuel = link.direction[direction][0];
                }

                if(in->key[SDL_SCANCODE_SPACE] && !space)
                {
                    creation_bombe(&link, &thread[0], map);
                    space = SDL_TRUE;
                }

                else if(!in->key[SDL_SCANCODE_SPACE] && space)
                    space = SDL_FALSE;

    /*--------------------------------------------------------------------------------------------------------------------------------*/

                if(in->key[SDL_SCANCODE_UP])   
                {
                    deplacer_joueur(&link_rouge, HAUT);
                    detecte_map(map, &link_rouge, &link, HAUT, LINK_ROUGE);
                }

                if(in->key[SDL_SCANCODE_DOWN])
                {
                    deplacer_joueur(&link_rouge, BAS);
                    detecte_map(map, &link_rouge, &link, BAS, LINK_ROUGE);
                }

                if(in->key[SDL_SCANCODE_LEFT])
                {
                    deplacer_joueur(&link_rouge, GAUCHE);
                    detecte_map(map, &link_rouge, &link, GAUCHE, LINK_ROUGE);
                }

                if(in->key[SDL_SCANCODE_RIGHT])
                {
                    deplacer_joueur(&link_rouge, DROITE);
                    detecte_map(map, &link_rouge, &link, DROITE, LINK_ROUGE);
                }

                if(in->key[SDL_SCANCODE_RCTRL] && !rctrl)
                {
                    creation_bombe(&link_rouge, &thread[1], map);
                    rctrl = SDL_TRUE;
                }

                else if(!in->key[SDL_SCANCODE_RCTRL] && rctrl)
                    rctrl = SDL_FALSE;
            } 

            else if (in->mouse[SDL_BUTTON_LEFT] && in->x >= 750 && in->x <= 1170)
            {
                if(in->y >= 491 && in->y <= 638)
                {
                    pthread_join(thread[0], NULL);
                    pthread_join(thread[1], NULL);
                    break;
                }

                else if(in->y >= 685 && in->y <= 833)
                    in->quit = 2;
            }

            limite_fps(frame_limit, 1); 
        }
    }

/*--------------------------------------------------------------------------------------------------------------------------------*/

    exite_statue = SDL_TRUE;

    quit_play:

    if(music != NULL)   
    {
        Mix_FreeMusic(music);
        printf("FREE_MUSIC\n");
    }

    if(explosion != NULL)
    {
        Mix_FreeChunk(explosion);
        printf("FREE_CHUNK : EXPLOSION\n");
    }

    for(i = 0 ; i < 3 ; i++)
        if(texture_victoire[i] != NULL)
        {
            SDL_DestroyTexture(texture_bombe[i]);
            printf("DESTROY_TEXTURE : TEXTURE_VICTOIRE[%d]\n", i);
        }

    if(link.direction_actuel != NULL)
    {
        SDL_DestroyTexture(link.direction_actuel);
        printf("DESTROY_TEXTURE : LINK.DIRECTION_ACTUEL\n");
        free_link(link.direction);
    }

    if(link_rouge.direction_actuel != NULL)
    {
        SDL_DestroyTexture(link_rouge.direction_actuel);
        printf("DESTROY_TEXTURE : LINK_ROUGE.DIRECTION_ACTUEL\n");
        free_link(link_rouge.direction);
    }

    for(i = 0 ; i < 3 ; i++)
        if(texture_bombe[i] != NULL)
        {
            SDL_DestroyTexture(texture_bombe[i]);
            printf("DESTROY_TEXTURE : TEXTURE_BOMBE[%d]\n", i);
        }

    if(texture_mur_destructible != NULL)
    {
        SDL_DestroyTexture(texture_mur_destructible);
        printf("DESTROY_TEXTURE : TEXTURE_MUR_DESTRUCTIBLE\n");
    }

    if(texture_arriere_plan != NULL)
    {
        SDL_DestroyTexture(texture_arriere_plan);
        printf("DESTROY_TEXTURE : TEXTURE_ARRIERE_PLAN\n");
    }

    pthread_join(thread[0], NULL);
    printf("PTHREAD_JOIN : THREAD[0]\n");
    pthread_join(thread[1], NULL);
    printf("PTHREAD_JOIN : THREAD[1]\n");
                
    return exite_statue;
}