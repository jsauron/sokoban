#include "../includes/sokoban.h"

void    active_game(t_win *wn)
{
  t_game        *game;
  SDL_Rect       pos;
  SDL_Rect       pos_player;

  int play = 1;
  game = wn->game;

  if (!upload_map(game->map))
  {
    printf("exit\n");
    exit(EXIT_FAILURE);
  }
  parse_map(game->map, &pos_player);
  SDL_PumpEvents();
  wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
  while (play)
  {
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
    fill_screen(wn, game, &pos, &pos_player,  game->map);
  }
    if (!game->goal) 
      play = 0;
}

int     fill_screen(t_win *wn, t_game *game,  SDL_Rect *pos, SDL_Rect *pos_player, int **map)
{
  int y;
  int x;

  y = 0;
  game->nb_goal = 0;
    while (y < YBLOC)
    {
      x = 0;
      while (x < XBLOC)
      {
        pos->x = x * SIZE_BLOC;
        pos->y = y * SIZE_BLOC;
        if (map[y][x] == WALL)
          SDL_BlitSurface(game->wall, NULL, wn->screen, pos);
        else if (map[y][x] == BLOC)
          SDL_BlitSurface(game->bloc, NULL, wn->screen, pos);
        else if (map[y][x] == BLOC_OK)
          SDL_BlitSurface(game->bloc_OK, NULL, wn->screen, pos);
        else if (map[y][x] == GOAL)
        {
          SDL_BlitSurface(game->goal, NULL, wn->screen, pos);
          game->nb_goal += 1;
        }
        x++;
      }
      y++;
    }
    pos->x = pos_player->x * SIZE_BLOC;
    pos->y = pos_player->y * SIZE_BLOC;
    SDL_BlitSurface(game->current_player, NULL, wn->screen, pos);

    render(wn);
    return (1);
}

int     parse_map(int **map, SDL_Rect *pos_player)
{
  int   y;
  int   x;

  y = 0;
    while(y < YBLOC)
    {
      x = 0;
      while(x < XBLOC)
      {
        if (map[y][x] == PLAYER)
        {
          pos_player->x = x;
          pos_player->y = y;
          map[y][x] = VIDE;
        }
        x++;
      }
      y++;
    }	
    return (1);
}

void    player_move(int **map, SDL_Rect *pos, int direction)
{
  switch (direction)
  {
    case UP:
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
























