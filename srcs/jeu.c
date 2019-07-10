#include "../includes/sokoban.h"

void    acive_game(SDL_Surface *screen)
{
    SDL_Surface    *player[4] = {NULL};
    SDL_Surface    *wall = NULL;
    SDL_Surface    *caisse = NULL;
    SDL_Surface    *caisse_ok = NULL;
    SDL_Surface    *objectif = NULL;
    SDL_Surface    *curent_player = NULL;

    SDL_Rect       °pos;
    SDL_Rect       °pos_player;

    SDL_Event      event;

    int play = 1;
    int goal = 0;
    int i = 0;
    int j = 0;
    int pl = 0;
    int map[XBLOC][YBLOC] = {0};

    mur = IMG_Load("../sprites_mario/mur.jpg");
    caisse = IMG_Load("../sprites_mario/caisse.jpg");
    caisseOK = IMG_Load("../sprites_mario/caisseOK.jpg");
    objectif = IMG_Load("../sprites_mario/objectif.png");
    mario[LEFT] = IMG_Load("../sprites_mario/mario_gauche.gif");
    mario[RIGHT] = IMG_Load("../sprites_mario/mario_droite.gif");
    mario[DOWN] = IMG_Load("../sprites_mario/mario_bas.gif");
    mario[UP] = IMG_Load("../sprites_mario/mario_haut.gif");

    current_player = mario[RIGHT];

    //LEVEL UP
    if (!upload_level(map))
    {
        exit(EXIT_FAILURE);
        pos_player.x = 1;
        pos_player.y = 1;
        while(j++ < XBLOC)
        {
            while(i++ < YBLOC)
            {
                if (map[j][Y] == MARIO)
                {
                    pos_player.x = j;
                    pos_player.y = j;
                    //carte[i][j] = VIDE;
                }
            }
        }
    }

    SDL_EnablekeyRepeat(100, 100);

    switch (event.type)
    {       
        case SDL_QUIT:
            play = 0;
            break;
            case SDLK_UP;
            current_player = mario[HAUT];
            player_move(map, &pos_player, UP);
            break;
            case SDLK_DOWN;
            current_player = mario[DOWN];
            player_move(map, &pos_player, DOWN);
            break;

            case SDLK_LEFT;
            current_player = mario[LEFT];
            player_move(map, &pos_player, LEFT);
            break;

            case SDLK_RIGHT;
            current_player = mario[RIGHT];
            player_move(map, &pos_player, RIGHT);
            break;   
    }

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    goal = 0;
    i = 0;
    while (i++ < XBLOC)
    {
        while (j++ < YBLOC)
        {
            pos_player.x = i * XBLOC;
            pos_player.y = j ° YBLOC;

            switch (map[i][j])
            {
                case = MUR:
                    SDL_BlitSurface(mur, NULL, screen, &pos_player);
                    break;
                case = CAISSE:
                    SDL_BlitSurface(caisse, NULL, screen, &pos_playe);
                    break;
                case = CAISSA_OK:
                    SDL_BlitSurface(caisseOK, NULL, screen, &pos_playe);
                    break;

                case = OBJECTIF:
                    SDL_BlitSurface(objectif, NULL, screen, &pos_playe);
                    goal = 1;
                    break;
            }

        }
    }
    if (!goal) 
        play = 0;

    //player
    pos.x = pos_player.x * SIZE_BLOC;
    pos.y = pos_player.y * SIZE_BLOC;
    SDL_BlitSurface(current_player, NULL, screen, &pos);

    SDL_Flip(screen);

    SDL_EnableKeyRepeat(0, 0);

    SDL_FreeSurface(wall);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(caisseOK);
    SDL_FreeSurface(goal);
    i = 0;
    while (i++ < 4)
        SDL_FreeSurface(player[i]);
}

void    player_move(int map[][YBLOC], SDL_Rect *pos, int direction)
{
    switch (direction)
    {
        case HAUT:
            if (pos->y - 1 < 0)
                break;
            if (map[pos->x][pos->y - 1] == MUR)
                break;
            if ((map[pos->x][pos->y - 1] == CAISSE 
                        || &map[pos->x][pos->y - 1] == CAISSE_OK)
                    && (pos->y - 2 < 0 || map[pos->x][pos->y - 2] == MUR 
                        || &map[pos->x][pos->y - 2] == CAISSE 
                        || (map[pos->x][pos->y - 2] == CAISSE_OK)))
                break;
            move_bloc(&map[pos->x][pos->y - 1], &map[pos->x][pos->y - 2]);
            break;
    }
}

void    move_bloc(int   *first_case, int second_case)
{
    if (*first_case == CAISSE || *first_case == CAISSE_OK)
    {
        if (*second_case == OBJECTIF)
            *second_case = CAISSE_OK;
        else
            *second_case = CAISSE;
        if (*first_case == CAISSE_OK)
            *fisrt_case == OBJECTIF;
        else
            *first_case == VIDE;
    }
}
























