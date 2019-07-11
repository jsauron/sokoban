#include "../includes/sokoban.h"

void    active_game(t_win *wn)
{
	t_game	*game;

	game = wn->game; 
	game->player_tab[0] = NULL;
	game->player_tab[1] = NULL;
	game->player_tab[2] = NULL;
	game->player_tab[3] = NULL;
	game->wall = NULL;
	game->bloc = NULL;
	game->bloc_OK = NULL;
	game->goal = NULL;
	game->current_player = NULL;

	SDL_Rect       pos;
	SDL_Rect       pos_player;

	int play = 1;
	int goal = 0;
	int x = 0;
	int y = 0;

	game->wall = IMG_Load("sprites_mario/mur.jpg");
	game->player_tab[UP] = IMG_Load("sprites_mario/mario_haut.gif");
	if(!game->player_tab[UP])
		printf("IMG_Load: %s\n", IMG_GetError());
	game->bloc = IMG_Load("sprites_mario/caisse.jpg");
	game->bloc_OK = IMG_Load("sprites_mario/caisse_OK.jpg");
	game->goal = IMG_Load("sprites_mario/objectif.png");
	game->player_tab[LEFT] = IMG_Load("sprites_mario/mario_gauche.gif");
	game->player_tab[RIGHT] = IMG_Load("sprites_mario/mario_droite.gif");
	game->player_tab[DOWN] = IMG_Load("sprites_mario/mario_bas.gif");
	game->current_player = game->player_tab[RIGHT];

	printf("ici\n");
	//LEVEL UP
	if (!upload_level(game->map))
	{
		printf("exit\n");
		exit(EXIT_FAILURE);
	}
	printf("ici cava \n");

	while(y < YBLOC)
	{
		x = 0;
		while(x < XBLOC)
		{
			if (game->map[y][x] == PLAYER)
			{
				pos_player.x = x;
				pos_player.y = y;
				game->map[y][x] = VIDE;
			}
			x++;
		}
		y++;
	}

	SDL_PumpEvents();
	wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
	while (play)
	{
		printf("play\n");
		//SDL_EnablekeyRepeat(100, 100);
		SDL_WaitEvent(&(wn->event));
		if (wn->event.type == SDL_QUIT || wn->state[SDL_SCANCODE_ESCAPE])
			play = 0;
		else if (wn->state[SDL_SCANCODE_UP])
		{
			game->current_player = game->player_tab[UP];
			player_move(game->map, &pos_player, UP);
		}
		else if (wn->state[SDL_SCANCODE_DOWN])
		{
			game->current_player = game->player_tab[DOWN];
			player_move(game->map, &pos_player, DOWN);
		}
		else if (wn->state[SDL_SCANCODE_LEFT])
		{
			game->current_player = game->player_tab[LEFT];
			player_move(game->map, &pos_player, LEFT);
		}
		else if (wn->state[SDL_SCANCODE_RIGHT])
		{
			game->current_player = game->player_tab[RIGHT];
			player_move(game->map, &pos_player, RIGHT);
		}

		SDL_FillRect(wn->screen, NULL, SDL_MapRGB(wn->screen->format, 255, 255, 255));
		goal = 0;
		y = 0;
		while (y < YBLOC)
		{
			x = 0;
			while (x < XBLOC)
			{
				pos.x = x * SIZE_BLOC;
				pos.y = y * SIZE_BLOC;
				if (game->map[y][x] == WALL)
					SDL_BlitSurface(game->wall, NULL, wn->screen, &pos);
				if (game->map[y][x] == BLOC)
					SDL_BlitSurface(game->bloc, NULL, wn->screen, &pos);
				if (game->map[y][x] == BLOC_OK)
					SDL_BlitSurface(game->bloc_OK, NULL, wn->screen, &pos);
				if (game->map[y][x] == GOAL)
				{
					SDL_BlitSurface(game->goal, NULL, wn->screen, &pos);
					goal = 1;
				}
				x++;
			}
			y++;
		}
		if (!goal) 
			play = 0;

		//player
		pos.x = pos_player.x * SIZE_BLOC;
		pos.y = pos_player.y * SIZE_BLOC;
		//wn->texture = SDL_CreateTextureFromSurface(wn->render, wn->screen);
		SDL_BlitSurface(game->current_player, NULL, wn->screen, &pos);
		SDL_UpdateTexture(wn->texture, NULL, wn->screen->pixels, wn->screen->pitch);
		SDL_RenderClear(wn->render);
		SDL_RenderCopy(wn->render, wn->texture, NULL, NULL);
		SDL_RenderPresent(wn->render);

	
	// SDL_EnableKeyRepeat(0, 0);

	//SDL_FreeSurface(game->wall);
	//SDL_FreeSurface(game->bloc);
	//SDL_FreeSurface(game->bloc_OK);
	//SDL_FreeSurface(game->goal);
	//i = 0;
	//while (i++ < 4)
	//SDL_FreeSurface(game->player_tab[i]);
	}
}

void    player_move(int **map, SDL_Rect *pos, int direction)
{
	switch (direction)
	{
		case UP:
			printf("pos->y = %d\n", pos->y);
			if (pos->y - 1 < 0)
				break;
			if (map[pos->y - 1][pos->x] == WALL)
				break;
			if ((map[pos->y - 1][pos->x] == BLOC
						|| map[pos->y - 1][pos->x] == BLOC_OK)
					&& (pos->y - 2 < 0 || map[pos->y - 2][pos->x] == WALL 
						|| map[pos->y - 2][pos->x] == BLOC
						|| (map[pos->y - 2][pos->x] == BLOC_OK)))
				break;
			printf("pos->y - 1 = %d\n", pos->y - 1);
			printf("pos->y - 2 = %d\n", pos->y - 2);
			move_bloc(&map[pos->y - 1 ][pos->x], &map[pos->y - 2][pos->x]);
			pos->y--;
			break;
		case DOWN:
			if (pos->y + 1 > 11)
				break;
			if (map[pos->y + 1][pos->x] == WALL)
				break;
			if ((map[pos->y + 1][pos->x] == BLOC 
						|| map[pos->y + 1][pos->x] == BLOC_OK)
					&& (pos->y + 2 > 11 || map[pos->y + 2][pos->x] == WALL 
						|| map[pos->y + 2][pos->x] == BLOC
						|| (map[pos->y + 2][pos->x] == BLOC_OK)))
				break;
			move_bloc( &map[pos->y + 1][pos->x], &map[pos->y + 2][pos->x]);
			pos->y++;
			break;
		case LEFT:
			if (pos->x - 1 < 0)
				break;
			if (map[pos->y][pos->x - 1] == WALL)
				break;
			if ((map[pos->y][pos->x - 1] == BLOC
						|| map[pos->y][pos->x - 1] == BLOC_OK)
					&& (pos->x - 2 < 0 || map[pos->y][pos->x - 2] == WALL 
						|| map[pos->y][pos->x - 2] == BLOC
						|| (map[pos->y][pos->x - 2] == BLOC_OK)))
				break;
			printf("pos-x - 1 = %d\n", pos->x - 1);
			printf("pos->x - 2 = %d\n", pos->x - 2);
			move_bloc(&map[pos->y - 1 ][pos->x], &map[pos->y - 2][pos->x]);
			move_bloc( &map[pos->y][pos->x - 1], &map[pos->y][pos->x - 2]);
			pos->x--;
			break;
		case RIGHT:
			if (pos->x + 1 > 11)
				break;
			if (map[pos->y][pos->x + 1] == WALL)
				break;
			if ((map[pos->y][pos->x + 1] == BLOC 
						|| map[pos->y][pos->x + 1] == BLOC_OK)
					&& (pos->x + 2 > 11 || map[pos->y][pos->x + 2] == WALL 
						|| map[pos->y][pos->x + 2] == BLOC
						|| (map[pos->y][pos->x + 2] == BLOC_OK)))
				break;
			move_bloc( &map[pos->y][pos->x + 1], &map[pos->y][pos->x + 2]);
			pos->x++;
			break;
	}
}

void    move_bloc(int *first_case, int *second_case)
{
	if (*first_case == BLOC || *first_case == BLOC_OK)
	{
		if (*second_case == GOAL)
			*second_case = BLOC_OK;
		else
			*second_case = BLOC;
		if (*first_case == BLOC_OK)
			*first_case = GOAL;
		else
			*first_case = VIDE;
	}
}
























