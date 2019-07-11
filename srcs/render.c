#include "sokoban.h"

int     render(t_win *wn)
{
SDL_UpdateTexture(wn->texture, NULL, wn->screen->pixels, wn->screen->pitch);
SDL_RenderClear(wn->render);
SDL_RenderCopy(wn->render, wn->texture, NULL, NULL);
SDL_RenderPresent(wn->render);
return (0);
}
