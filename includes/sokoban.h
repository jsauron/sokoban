
#ifndef SOKOBAN_H
# define SOKOBAN_H

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <stdlib.h>

/* constante */

#define SIZE_BLOC	34
#define XBLOC		12
#define YBLOC		12
#define	XSCREEN		SIZE_BLOC * XBLOC
#define YSCREEN		SIZE_BLOC * YBLOC

enum {UP, DOWN, LEFT, RIGHT};
enum {VIDE, WALL, BLOC, GOAL, PLAYER, BLOC_OK};

typedef struct		s_game
{
	SDL_Surface		*player_tab[4];
	SDL_Surface		*player;
	SDL_Surface		*wall;
	SDL_Surface		*bloc;
	SDL_Surface		*bloc_OK;
	SDL_Surface		*goal;
	SDL_Surface		*current_player;

}					t_game;

typedef struct		s_win
{
	SDL_Window		*window;
	SDL_Surface*	screen;
	SDL_Surface		*menu;
	SDL_Surface		*icon;
	SDL_Rect		pos_menu;
	SDL_Renderer	*render;
	SDL_Texture		*texture;
	SDL_Event		event;
	t_game			*game;

}				t_win;

/* Editor.c */
void	editor(t_win *wn, t_game *game);

/* File.c */
int		upload_level(int level[][YBLOC]);
int		save_level(int level[][YBLOC]);

/* Jeu.c */
void    move_bloc(int   first_case, int second_case);
void    player_move(int map[][YBLOC], SDL_Rect *pos, int direction);
void    active_game(t_win *wn);

/* main.c */
int		main();

#endif
