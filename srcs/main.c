#include "sokoban.h"

int	main()
{
  t_win			*wn;
  int				i = 1;;
  int play = 1;
  i = 0;

  wn = NULL;
  wn = init(wn);
  SDL_PumpEvents();
  wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
  while (play)
  {
    SDL_WaitEvent(&(wn->event));
    if (wn->event.type == SDL_QUIT || wn->state[SDL_SCANCODE_ESCAPE])
      play = 0;
    else if (wn->state[SDL_SCANCODE_ESCAPE])
      play = 0;
    else if (wn->state[SDL_SCANCODE_1])
      active_game(wn);
    else if (wn->state[SDL_SCANCODE_2])
      editor(wn, wn->game);
    SDL_BlitSurface(wn->menu, NULL, wn->screen, &(wn->pos_menu));
    SDL_UpdateTexture(wn->texture, NULL, wn->screen->pixels, wn->screen->pitch);
    SDL_RenderClear(wn->render);
    SDL_RenderCopy(wn->render, wn->texture, NULL, NULL);
    SDL_RenderPresent(wn->render);
  }
  SDL_FreeSurface(wn->menu);
  SDL_Quit();

  return (0);
}

