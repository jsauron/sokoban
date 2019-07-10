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
//	SDL_SetRenderDrawColor(wn->render, 255, 0, 255, 255);
	wn->menu = IMG_Load("sprites_mario/menu.jpg");
	if(!wn->menu)
		printf("IMG_Load: %s\n", IMG_GetError());
	wn->pos_menu.x = 0;
	wn->pos_menu.y = 0;

	wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
	while (play)
	{
		SDL_WaitEvent(&(wn->event));
		if (wn->event.type == SDL_QUIT || wn->state[SDL_SCANCODE_ESCAPE])
			play = 0;
		else if  (wn->event.type == SDL_KEYDOWN)
		{
			if (wn->state[SDL_SCANCODE_ESCAPE])
				play = 0;
			else if (wn->state[SDL_SCANCODE_1])
			{
				printf("active\n");
				active_game(wn);
			}
			else if (wn->state[SDL_SCANCODE_2])
				editor(wn, wn->game);
		}
		SDL_FillRect(wn->screen, NULL, SDL_MapRGB(wn->screen->format, 250, 0, 250));
		SDL_BlitSurface(wn->menu, NULL, wn->screen, &(wn->pos_menu));
	//	wn->texture = SDL_CreateTextureFromSurface(wn->render, wn->menu);
		SDL_UpdateTexture(wn->texture, NULL, wn->screen->pixels, wn->screen->pitch);
	//	SDL_RenderClear(wn->render);
		SDL_RenderCopy(wn->render, wn->texture, NULL, NULL);
		SDL_RenderPresent(wn->render);
	}
	SDL_FreeSurface(wn->menu);
	SDL_Quit();

	return (0);
}

