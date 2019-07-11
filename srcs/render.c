#include "sokoban.h"
int     free_game(t_win *wn, t_game *game)
{
  SDL_FreeSurface(wn->menu);
  SDL_FreeSurface(game->wall);
  SDL_FreeSurface(game->bloc);
  SDL_FreeSurface(game->bloc_OK);
  SDL_FreeSurface(game->goal);
  int i = 0;
  while (i < 4)
    SDL_FreeSurface(game->player_tab[i++]);
  return (1);
}
int     render(t_win *wn)
{
  SDL_UpdateTexture(wn->texture, NULL, wn->screen->pixels, wn->screen->pitch);
  SDL_RenderClear(wn->render);
  SDL_RenderCopy(wn->render, wn->texture, NULL, NULL);
  SDL_RenderPresent(wn->render);
  return (0);
}
