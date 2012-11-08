#ifndef GLOGIC_H
#define GLOGIC_H

#include "vector.h"
#include "config.h"


SDL_Rect calcEnemyPos(zombie enemy, SDL_Rect player, float speed);
SDL_Rect calcEnemyPosRanged(zombie enemy, SDL_Rect player, int range, vec2f *rndMovement);
zbox calcRandomMovement(zombie src, vec2f *basevec);
int isInRange(zbox src, zbox target, int range);
int collides(zbox a, zbox b);
zombie updatePlayer(zombie player, Uint8 *keys);

#endif