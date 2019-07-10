#include "../includes/sokoban.h"

void    active_game(struct t_win *wn)
{
	struct t_game	*game;

	game = wn->game; 
	game = wn->game;
    //game->player_tab[4];/* = {NULL, NULL, NULL, NULL};*/
    game->wall = NULL;
    game->bloc = NULL;
    game->bloc_OK = NULL;
    game->goal = NULL;
    game->current_player = NULL;

    SDL_Rect       pos;
    SDL_Rect       pos_player;

    SDL_Event      event;

    int play = 1;
    int goal = 0;
    int i = 0;
    int j = 0;
   // int play = 0;
    int map[XBLOC][YBLOC] = {/*0*/};

    game->wall = IMG_Load("../sprites_mario/mur.jpg");
    game->bloc = IMG_Load("../sprites_mario/caisse.jpg");
    game->bloc_OK = IMG_Load("../sprites_mario/caisseOK.jpg");
    game->goal = IMG_Load("../sprites_mario/objectif.png");
    game->player_tab[LEFT] = IMG_Load("../sprites_mario/mario_gauche.gif");
    game->player_tab[RIGHT] = IMG_Load("../sprites_mario/mario_droite.gif");
    game->player_tab[DOWN] = IMG_Load("../sprites_mario/mario_bas.gif");
    game->player_tab[UP] = IMG_Load("../sprites_mario/mario_haut.gif");

    game->current_player = game->player_tab[RIGHT];

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
                if (map[j][i] == PLAYER)
                {
                    pos_player.x = j;
                    pos_player.y = j;
                    map[j][i] = VIDE;
                }
            }
        }
    }

    //SDL_EnablekeyRepeat(100, 100);

    switch (event.type)
    {       
        case SDL_QUIT:
            play = 0;
            break;
		case SDL_SCANCODE_UP:
            game->current_player = game->player_tab[UP];
            player_move(map, &pos_player, UP);
            break;
		case SDL_SCANCODE_DOWN:
            game->current_player = game->player_tab[DOWN];
            player_move(map, &pos_player, DOWN);
            break;

		case SDL_SCANCODE_LEFT:
            game->current_player = game->player_tab[LEFT];
            player_move(map, &pos_player, LEFT);
            break;

		case SDL_SCANCODE_RIGHT:
            game->current_player = game->player_tab[RIGHT];
            player_move(map, &pos_player, RIGHT);
            break;   
    }

    SDL_FillRect(wn->screen, NULL, SDL_MapRGB(wn->screen->format, 255, 255, 255));
    goal = 0;
    i = 0;
    while (i++ < XBLOC)
    {
        while (j++ < YBLOC)
        {
            pos_player.x = i * XBLOC;
            pos_player.y = j * YBLOC;

            switch (map[i][j])
            {
                case  WALL:
                    SDL_BlitSurface(game->wall, NULL, wn->screen, &pos_player);
                    break;
                case  BLOC:
                    SDL_BlitSurface(game->bloc, NULL, wn->screen, &pos_player);
                    break;
                case  BLOC_OK:
                    SDL_BlitSurface(game->bloc_OK, NULL, wn->screen, &pos_player);
                    break;

                case  GOAL:
                    SDL_BlitSurface(game->goal, NULL, wn->screen, &pos_player);
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
	SDL_Texture *texture = SDL_CreateTextureFromSurface(wn->render, wn->screen);
	
	SDL_RenderClear(wn->render);

	SDL_RenderCopy(wn->render, texture, NULL, NULL);

	SDL_RenderPresent(wn->render);

    SDL_BlitSurface(game->current_player, NULL, wn->screen, &pos);

   // SDL_EnableKeyRepeat(0, 0);

    SDL_FreeSurface(game->wall);
    SDL_FreeSurface(game->bloc);
    SDL_FreeSurface(game->bloc_OK);
    SDL_FreeSurface(game->goal);
    i = 0;
    while (i++ < 4)
        SDL_FreeSurface(game->player_tab[i]);
}

void    player_move(int map[][YBLOC], SDL_Rect *pos, int direction)
{
    switch (direction)
    {
        case UP:
            if (pos->y - 1 < 0)
                break;
            if (map[pos->x][pos->y - 1] == WALL)
                break;
            if ((map[pos->x][pos->y - 1] == BLOC
                        || map[pos->x][pos->y - 1] == BLOC_OK)
                    && (pos->y - 2 < 0 || map[pos->x][pos->y - 2] == WALL 
                        || map[pos->x][pos->y - 2] == BLOC
                        || (map[pos->x][pos->y - 2] == BLOC_OK)))
                break;
            move_bloc(map[pos->x][pos->y - 1], map[pos->x][pos->y - 2]);
			pos->y--;
            break;
          case DOWN:
            if (pos->y + 1 < 0)
                break;
            if (map[pos->x][pos->y + 1] == WALL)
                break;
            if ((map[pos->x][pos->y + 1] == BLOC 
                        || map[pos->x][pos->y + 1] == BLOC_OK)
                    && (pos->y + 2 < 0 || map[pos->x][pos->y + 2] == WALL 
                        || map[pos->x][pos->y + 2] == BLOC
                        || (map[pos->x][pos->y + 2] == BLOC_OK)))
                break;
            move_bloc( map[pos->x][pos->y + 1], map[pos->x][pos->y + 2]);
			pos->y++;
            break;
        case LEFT:
            if (pos->x - 1 < 0)
                break;
            if (map[pos->x - 1][pos->y] == WALL)
                break;
            if ((map[pos->x - 1][pos->y] == BLOC
                        || map[pos->x - 1][pos->y] == BLOC_OK)
                    && (pos->x - 2 < 0 || map[pos->x - 2][pos->y] == WALL 
                        || map[pos->x - 2][pos->y] == BLOC
                        || (map[pos->x - 2][pos->y] == BLOC_OK)))
                break;
            move_bloc( map[pos->x - 1][pos->y], map[pos->x - 2][pos->y]);
			pos->x--;
            break;
        case RIGHT:
            if (pos->x + 1 < 0)
                break;
            if (map[pos->x + 1][pos->y] == WALL)
                break;
            if ((map[pos->x + 1][pos->y] == BLOC 
						|| map[pos->x + 1][pos->y] == BLOC_OK)
                    && (pos->x + 2 < 0 || map[pos->x + 2][pos->y] == WALL 
                        || map[pos->x + 2][pos->y] == BLOC
                        || (map[pos->x + 2][pos->y] == BLOC_OK)))
                break;
            move_bloc( map[pos->x + 1][pos->y], map[pos->x + 2][pos->y]);
			pos->x++;
            break;
 
    }
}

void    move_bloc(int first_case, int second_case)
{
    if (first_case == BLOC || first_case == BLOC_OK)
    {
        if (second_case == GOAL)
            second_case = BLOC_OK;
        else
            second_case = BLOC;
        if (first_case == BLOC_OK)
            first_case = GOAL;
        else
            first_case = VIDE;
    }
}
























