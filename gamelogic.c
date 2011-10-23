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

SDL_Rect calcEnemyPosRanged(zombie enemy, SDL_Rect player, int range, float speed)
{
	if(isInRange(enemy.rect, player, range))
	{
		vec2f vec = basicv2f(v2f((float)player.x,(float)player.y,(float)enemy.rect.x,(float)enemy.rect.y));
		vec = smulv2f(enemy.speed,vec);
		enemy.rect.x -= (int) vec.x;
		enemy.rect.y -= (int) vec.y;
		enemy.rect.w = enemy.rect.h = SQR_SIZE;		
		return enemy.rect;
	}
	else
	{
		return enemy.rect;
	}
}

int isInRange(zbox src, zbox target, int range) // looks if target is in scr's field of view
{
	if(src.x+range>target.x-P_SIZE/2&&src.x-range<target.x+P_SIZE/2) // is the target's x in field of view, ...
	{
		if(src.y+range>target.y+P_SIZE/2&&src.y-range<target.y-P_SIZE/2) // ... and is the target's y in the field of view
		{
			return 1; // so return "true"
		}
	}
	return 0;
}

int collides(zbox a, zbox b)
{
	if()
	{
		if()
		{
			
		}
	}
}
