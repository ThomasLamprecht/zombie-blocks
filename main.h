#include <stdlib.h>
#include <stdio.h>
#ifndef SDL_H
	#define SDL_H
	#include <SDL/SDL.h>
#endif
#ifndef VECTOR_H
	#define VECTOR_H
	#include "vector.h"
#endif
#ifndef GLOGIC_H
	#define GLOGIC_H
	#include "gamelogic.h"
#endif
#ifndef TYPES_H
	#define TYPES_H
	#include "types.h"
#endif

#define ZOMBIES 40
#define SQR_SIZE 10

SDL_Surface *window(int width, int height, int bpp, Uint32 flags, char *window_title, char *icon_title);
SDL_Rect calcEnemyPos(zombie enemy, SDL_Rect player, float speed);

const float zombie_speed = 2.5f;