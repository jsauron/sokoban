#include "../includes/sokoban.h"

int	main(int ac, char **av)
{
    SDL_Surface	*screen;
    SDL_Rect	pos_menu;
    SDL_Event	event;

    int play = 1;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("../sprites_mario/caisse.jpg"), NULL);
    screen = SDL_SetVideoMode(XSCREEN, YSCREEN, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Mario Sokoban", NULL);

    menu = IMG_Load("menu.jpg");
    pos_menu.x = 0;
    pos_menu.y = 0;

    while (play)
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT)
            play = 0;
        else if  (event.type == SDL_Keydown)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
                play = 0;
            else if (event.key.keysym.sym == SDLK_KP1)
                active_game(screen);
            else if (event.key.keysym.sym == SDLK_KP2)
                editor(screen);
        }				

    
        SDL_FillRect(screen, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(menu, NULL, screen, pos_menu);
        SDL_Flip(screen);    
    }
    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCESS;
}

