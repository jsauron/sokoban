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
	int i = 0;
	int j = 0;

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

	while(j < XBLOC)
	{
		i = 0;
		while(i < YBLOC)
		{
			if (game->map[j][i] == PLAYER)
			{
				pos_player.x = j;
				pos_player.y = i;
				game->map[j][i] = VIDE;
			}
			i++;
		}
		j++;
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
		i = 0;
		while (i < XBLOC)
		{
			j = 0;
			while (j < YBLOC)
			{
				pos.x = i * SIZE_BLOC;
				pos.y = j * SIZE_BLOC;
				if (game->map[i][j] == WALL)
					SDL_BlitSurface(game->wall, NULL, wn->screen, &pos);
				if (game->map[i][j] == BLOC)
					SDL_BlitSurface(game->bloc, NULL, wn->screen, &pos);
				if (game->map[i][j] == BLOC_OK)
					SDL_BlitSurface(game->bloc_OK, NULL, wn->screen, &pos);
				if (game->map[i][j] == GOAL)
				{
					SDL_BlitSurface(game->goal, NULL, wn->screen, &pos);
					goal = 1;
				}
				j++;
			}
			i++;
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
























