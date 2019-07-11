/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 10:49:12 by jsauron           #+#    #+#             */
/*   Updated: 2019/07/11 13:35:55 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sokoban.h"

void	editor(t_win *wn, t_game *game)
{
	SDL_Rect pos;

	int play = 1;
	int left_click = 0;
	int right_click = 0;
	int current_obj = WALL;
	int x = 0;
	int y = 0;

	game->wall = IMG_Load("sprites_mario/mur.jpg");
	game->bloc = IMG_Load("sprites_mario/caisse.jpg");
	game->goal = IMG_Load("sprites_mario/objectif.png");
	game->player = IMG_Load("sprites_mario/mario_bas.gif");

	if(!upload_level(game->map))
		exit(EXIT_FAILURE);

	while (play)
	{
	if (wn->event.type == SDL_QUIT)
		play = 0;
	else if (wn->event.type ==  SDL_MOUSEBUTTONDOWN)
	{
		if (wn->event.button.button == SDL_BUTTON_LEFT)
		{
			game->map[wn->event.button.x / SIZE_BLOC][wn->event.button.y / SIZE_BLOC] = current_obj;
			left_click = 1;
		}
		if (wn->event.button.button == SDL_BUTTON_RIGHT)
		{
			game->map[wn->event.button.x / SIZE_BLOC][wn->event.button.y / SIZE_BLOC] = VIDE;
			right_click = 1;
		}
	}
	else if (wn->event.type ==  SDL_MOUSEBUTTONUP)
	{
		if (wn->event.button.button == SDL_BUTTON_LEFT)
			left_click = 0;
		else if (wn->event.button.button == SDL_BUTTON_RIGHT)
			right_click = 0;
	}
	if (wn->event.type ==  SDL_MOUSEMOTION)
	{
		if (left_click)
			game->map[wn->event.motion.x / SIZE_BLOC][wn->event.motion.y / SIZE_BLOC] = current_obj;
		else if (right_click)
			game->map[wn->event.motion.x / SIZE_BLOC][wn->event.motion.y / SIZE_BLOC] = VIDE;
	}
	if (wn->event.type == SDL_KEYDOWN)
	{
		switch(wn->event.key.keysym.sym)
		{
			case SDL_SCANCODE_ESCAPE:
				play= 0;
				break;
			case SDL_SCANCODE_S:
				save_level(game->map);
				break;
			case SDL_SCANCODE_C:
				save_level(game->map);
				break;
			case SDL_SCANCODE_1:
				current_obj = WALL;
				break;
			case SDL_SCANCODE_2:
				current_obj = BLOC;
				break;
			case SDL_SCANCODE_3:
				current_obj = GOAL;
				break;
			case SDL_SCANCODE_4:
				current_obj = PLAYER;
				break;
		}
	}
	SDL_FillRect(wn->screen ,NULL, SDL_MapRGB(wn->screen->format, 255, 255, 255));
	y = 0;
	while (y < XBLOC)
	{
		x = 0;
		while (x < YBLOC)
		{
			pos.x = x * SIZE_BLOC;
			pos.y = y * SIZE_BLOC;
			switch (game->map[y][x])
			{
				case  WALL:
					SDL_BlitSurface(game->wall, NULL, wn->screen, &pos);
					break;
				case BLOC:
					SDL_BlitSurface(game->bloc, NULL, wn->screen, &pos);
					break;
				case GOAL:
					SDL_BlitSurface(game->goal, NULL, wn->screen, &pos);
					break;
				case PLAYER:
					SDL_BlitSurface(game->goal, NULL, wn->screen, &pos);
					break;
			}
			x++;
		}
		y++;
	}
	SDL_UpdateTexture(wn->texture, NULL, wn->screen->pixels, wn->screen->pitch);
	SDL_RenderClear(wn->render);
	//SDL_CreateTextureFromSurface(wn->render, wn->screen);
	SDL_RenderCopy(wn->render, wn->texture, NULL, NULL);

	SDL_RenderPresent(wn->render);
	}
	SDL_FreeSurface(game->wall);
	SDL_FreeSurface(game->bloc);
	SDL_FreeSurface(game->goal);
	SDL_FreeSurface(game->player);
}






