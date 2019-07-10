#ifndef SOKOBAN_H
# define SOKOBAN_H

/* constante */

#define SIZE_BLOC	34
#define XBLOC		12
#define YBLOC		12
#define	XSCREEN		SIZE_BLOC * XBLOC
#define YSCREEN		SIZE_BLOC * YBLOC

enum {UP, DOWN, LEFT, RIGHT};		
enum {VIDE, MUR, CAISSE, OBJECTIF, MARIO, CAISSE_OK};		

#include <SDL.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdioh.h>
#include <stdlib.h>

#endif
