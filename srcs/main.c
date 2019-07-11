#include "sokoban.h"

int	main()
{
  t_win			*wn;
  int       play;

  wn = NULL;
  play = 1;

  wn = init(wn);
  //  SDL_PumpEvents();
  wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
  while (play)
  {
    SDL_WaitEvent(&(wn->event));
    if (wn->event.type == SDL_QUIT || wn->state[SDL_SCANCODE_ESCAPE])
      play = 0;
    else if (wn->state[SDL_SCANCODE_1])
      active_game(wn);
    else if (wn->state[SDL_SCANCODE_2])
      editor(wn, wn->game);
    SDL_BlitSurface(wn->menu, NULL, wn->screen, &(wn->pos_menu));
    render(wn);
  }
  SDL_FreeSurface(wn->menu);
  SDL_Quit();

  return (0);
}

