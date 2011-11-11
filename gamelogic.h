#ifndef VECTOR_H
	#define VECTOR_H
	#include "vector.h"
#endif
#ifndef CFG_H
	#define CFG_H
	#include "config.h"
#endif

SDL_Rect calcEnemyPos(zombie enemy, SDL_Rect player, float speed);
SDL_Rect calcEnemyPosRanged(zombie enemy, SDL_Rect player, int range, vec2f *rndMovement);
zbox calcRandomMovement(zombie src, vec2f *basevec);
int isInRange(zbox src, zbox target, int range);
int collides(zbox a, zbox b);
