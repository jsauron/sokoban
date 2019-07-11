#include "sokoban.h"

t_win   *init(t_win  *wn)
{
  int i;

  i = 0;
  if (!(wn = malloc(sizeof(t_win ))))
    exit (1);
  if (!(wn->game = malloc(sizeof(t_game ))))
    exit (1);
  if (!(wn->game->map = malloc(sizeof(int *) * XBLOC)))
    exit (1);
  while (i < XBLOC)
    wn->game->map[i++] = malloc(sizeof(int) * YBLOC);
  init_structure(wn, wn->game);
  init_sdl(wn);
  return (wn);
}

int init_sdl(t_win *wn)
{
  SDL_Init(SDL_INIT_VIDEO);

  wn->window = SDL_CreateWindow("SOKOBAN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, XSCREEN, YSCREEN, 0);
  wn->icon = IMG_Load("sprites_mario/caisse.jpg");
  SDL_SetWindowIcon(wn->window, wn->icon);
  wn->render = SDL_CreateRenderer(wn->window, -1, 0);
  wn->screen = SDL_CreateRGBSurface(0, XSCREEN, YSCREEN, 32,
      0x00FF0000,
      0x0000FF00,
      0x000000FF,
      0xFF000000);
  wn->texture = SDL_CreateTexture(wn->render,
      SDL_PIXELFORMAT_ARGB8888,
      SDL_TEXTUREACCESS_STREAMING,
      XSCREEN, YSCREEN);
  return (1);
}

int  init_structure(t_win *wn, t_game *game)
{
  printf("kkkkk\n");
  wn->menu = IMG_Load("sprites_mario/menu_soko.jpg");
  wn->pos_menu.x = 0;
  wn->pos_menu.y = 0;

  game->player_tab[0] = NULL;
  game->player_tab[1] = NULL;
  game->player_tab[2] = NULL;
  game->player_tab[3] = NULL;
  game->wall = NULL;
  game->bloc = NULL;
  game->bloc_OK = NULL;
  game->goal = NULL;
  game->current_player = NULL;

  game->wall = IMG_Load("sprites_mario/mur.jpg");
  game->bloc = IMG_Load("sprites_mario/caisse.jpg");
  game->bloc_OK = IMG_Load("sprites_mario/caisse_OK.jpg");
  game->goal = IMG_Load("sprites_mario/objectif.png");
  game->player_tab[LEFT] = IMG_Load("sprites_mario/mario_gauche.gif");
  game->player_tab[RIGHT] = IMG_Load("sprites_mario/mario_droite.gif");
  game->player_tab[DOWN] = IMG_Load("sprites_mario/mario_bas.gif");
  game->player_tab[UP] = IMG_Load("sprites_mario/mario_haut.gif");
  game->current_player = game->player_tab[RIGHT];
  return (1);
}
