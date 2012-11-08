#include <stdlib.h>
#include <stdio.h>
#ifndef SDL_H
	#define SDL_H
	#include <SDL/SDL.h>
#endif

#include "vector.h"
#include "gamelogic.h"
#include "types.h"
#include "config.h"

//#define ZOMBIES 50
//#define SQR_SIZE 20

SDL_Surface *window(int width, int height, int bpp, Uint32 flags, char *window_title, char *icon_title);
//SDL_Rect calcEnemyPos(zombie enemy, SDL_Rect player, float speed);

const float ZOMBIE_SPEED = 1.f; // optium between 2 & 3.5
const float PLAYER_SPEED = 4.3f; 
