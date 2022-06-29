#include "source.h"

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("ERREUR : INIT_VIDEO > %s\n",SDL_GetError());
        return -1;
    }

    if(SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, window, renderer) != 0)
    {
        SDL_Log("ERREUR : CREATE_WINDOW_OR_RENDERER > %s\n",SDL_GetError());
        return -1;
    }
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

SDL_Texture *load_image(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *image = NULL;
    SDL_Texture *texture = NULL;

    image = IMG_Load(path);
    if(image == NULL)
    {
        SDL_Log("ERREUR : LOAD_IMAGE > %s\n",SDL_GetError());
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    if(texture == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        return NULL;
    }
    return texture;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void free_link(SDL_Texture *link[])
{
    int i;

    for(i = 0 ; i < 4 ; i++) 
        if(link[i] != NULL)
            SDL_DestroyTexture(link[i]);
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int create_link(SDL_Texture *link[], SDL_Renderer *renderer, SDL_Rect taille_link[])
{
    int i;

    for(i = 0 ; i < 4 ; i++)
    {
        taille_link[i].x = 0;
        taille_link[i].y = 0;
    }

    for(i = 2 ; i < 4 ; i++)
    {
        taille_link[i].h = 110;
        taille_link[i].w = 85;
        taille_link[i - 2].w = 90;
    }

    link[0] = load_image("src/images/link_dos.png", renderer);
    if(link[0] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link);
        return -1;
    }
    taille_link[0].h = 105;

    link[1] = load_image("src/images/link_face.png", renderer);
    if(link[1] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link);
        return -1;
    }
    taille_link[1].h = 115;
    
    link[2] = load_image("src/images/link_gauche.png", renderer);
    if(link[2] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link);
        return -1;
    }

    link[3] = load_image("src/images/link_droite.png", renderer);
    if(link[3] == NULL)
    {
        SDL_Log("ERREUR : CREATE_TEXTURE > %s\n",SDL_GetError());
        free_link(link);
        return -1;
    }

    return 0;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void destroy_play(SDL_Texture *texture_arriere_plan, SDL_Texture *link_actuel, SDL_Texture *link[])
{
    SDL_DestroyTexture(texture_arriere_plan);
    SDL_DestroyTexture(link_actuel);
    free_link(link);
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int play(SDL_Renderer *renderer)
{
    SDL_Event event;
    SDL_bool game_launched = SDL_TRUE;
    SDL_Texture *texture_arriere_plan = NULL, *link[4], *link_actuel = NULL;
    SDL_Rect taille_link_actuel, taille_link[4];

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

    printf("%d\n%d\n%d\n%d\n",taille_link_actuel.h, taille_link_actuel.w, taille_link_actuel.x, taille_link_actuel.y);

    while (game_launched)
    {
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

        while(SDL_PollEvent(&event) == 1)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                destroy_play(texture_arriere_plan, link_actuel, link);
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

    destroy_play(texture_arriere_plan, link_actuel, link);
                
    return 0;
}