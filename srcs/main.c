#include "sokoban.h"

int	main()
{
	t_win			*wn;

	if (!(wn = malloc(sizeof(t_win ))))
		exit (1);
	if (!(wn->game = malloc(sizeof(t_game))))
		exit (1);
	
		int play = 1;

	SDL_Init(SDL_INIT_VIDEO);

	wn->window = SDL_CreateWindow("SOKOBAN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, XSCREEN, YSCREEN, SDL_WINDOW_RESIZABLE);
	wn->icon = IMG_Load("../sprites_mario/caisse.jpg"); 
	SDL_SetWindowIcon(wn->window, wn->icon);
	wn->screen = SDL_CreateRGBSurface(0, XSCREEN, YSCREEN, 32,
			0x00FF0000,
			0x0000FF00,
			0x000000FF,
			0xFF000000);
	/*SDL_Texture *sdlTexture = SDL_CreateTexture(sdlRenderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			XSCREEN, YSCREEN);
*/
	wn->render = SDL_CreateRenderer(wn->window, -1, 0);
	wn->menu = IMG_Load("menu.jpg");
	wn->pos_menu.x = 0;
	wn->pos_menu.y = 0;

	while (play)
	{
		SDL_WaitEvent(&(wn->event));
		if (wn->event.type == SDL_QUIT)
			play = 0;
		else if  (wn->event.type == SDL_KEYDOWN)
		{
			if (wn->event.key.keysym.sym == SDL_SCANCODE_ESCAPE)
				play = 0;
			else if (wn->event.key.keysym.sym == SDL_SCANCODE_1)
				active_game(wn);
			else if (wn->event.key.keysym.sym == SDL_SCANCODE_2)
				editor(wn, wn->game);
		}

		SDL_FillRect(wn->screen, NULL, SDL_MapRGB(wn->screen->format, 0, 0, 0));
		SDL_BlitSurface(wn->menu, NULL, wn->screen, &(wn->pos_menu));
	//	sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, mySurface);
		SDL_RenderPresent(wn->render);
	}
	SDL_FreeSurface(wn->menu);
	SDL_Quit();

	return (0);
}

