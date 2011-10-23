#ifndef GLOGIC_H
	#define GLOGIC_H
	#include "gamelogic.h"
#endif

SDL_Rect calcEnemyPos(zombie enemy, SDL_Rect player, float speed)
{
	vec2f vec = basicv2f(v2f((float)player.x,(float)player.y,(float)enemy.rect.x,(float)enemy.rect.y));
	vec = smulv2f(enemy.speed,vec);
	enemy.rect.x -= (int) vec.x;
	enemy.rect.y -= (int) vec.y;
	enemy.rect.w = enemy.rect.h = SQR_SIZE;
	return enemy.rect;
}
