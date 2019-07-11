
#ifndef SOKOBAN_H
# define SOKOBAN_H

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

/* constante */

#define SIZE_BLOC	34
#define XBLOC		12
#define YBLOC		12
#define	XSCREEN		SIZE_BLOC * XBLOC
#define YSCREEN		SIZE_BLOC * YBLOC

enum {UP, DOWN, LEFT, RIGHT};
enum {VIDE, WALL, BLOC, GOAL, PLAYER, BLOC_OK};

typedef	struct		s_mouse
{
  Uint32	mouse;
  int		x;
  int		y;
}					t_mouse;

typedef struct		s_game
{
  SDL_Surface		*player_tab[4];
  SDL_Surface		*player;
  SDL_Surface		*wall;
  SDL_Surface		*bloc;
  SDL_Surface		*bloc_OK;
  SDL_Surface		*goal;
  SDL_Surface		*current_player;
  int				**map;

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
  Uint8			*state;
  t_mouse			input;
  t_game			*game;
}				t_win;

/* editor.c */
void	editor(t_win *wn, t_game *game);

/* file.c */
int		upload_level(int **level);
int		save_level(int **level);

/* jeu.c */
void    move_bloc(int   *first_case, int *second_case);
void    player_move(int **map, SDL_Rect *pos, int direction);
void    active_game(t_win *wn);

/* init.c*/
t_win   *init(t_win  *wn);
int   malloc_structure(t_win *wn);
int   init_sdl(t_win *win);
int   init_structure(t_win *wn, t_game *game);

/* main.c */
int		main();

#endif
