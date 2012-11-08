#include "gamelogic.h"

SDL_Rect calcEnemyPos(zombie enemy, SDL_Rect player, float speed)
{
	vec2f vec = basicv2f(v2f((float)player.x,(float)player.y,(float)enemy.rect.x,(float)enemy.rect.y));
	vec = smulv2f(enemy.speed,vec);
	enemy.rect.x -= (int) vec.x;
	enemy.rect.y -= (int) vec.y;
	enemy.rect.w = enemy.rect.h = SQR_SIZE;
	return enemy.rect;
}

SDL_Rect calcEnemyPosRanged(zombie enemy, SDL_Rect player, int range, vec2f *rndMovement)
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
		return calcRandomMovement(enemy, rndMovement);
	}
}

int isInRange(zbox src, zbox target, int range) // looks if target is in scr's field of view
{
	int srchalf = src.w;
	if(src.x+range+srchalf >= target.x && src.x-range <= target.x+P_SIZE) // is the target's x in field of view, ...
	{
		if(src.y+srchalf+range >= target.y+P_SIZE && src.y-range <= target.y+P_SIZE) // ... and is the target's y in the field of view
		{
			return 1; // so return "true"
		}
	}
	return 0;
}

int collideBoxes(zbox a, zbox b)
{
	int aw = a.w, bw = b.w;
	if(a.x+aw >= b.x && a.x <= b.x+bw)
	{
		if(a.y+aw >= b.y && a.y <= b.y+bw)
		{
			return 1;
		}
	}
	return 0;
}

zbox calcRandomMovement(zombie src, vec2f *basevec)
{
	vec2f tmp;
	int sign = ((rand()%2)?-1:1);
	//basevec->x += (sign<0)?((basevec->x-0.0005f<-1.f)?1:sign):((basevec->x+0.0005f>1.f)?-1:sign)*(rand()%100)/200000;
	//basevec->y = ((rand()%2)?-1:1)*sqrtf(1-pow(basevec->x,2));
	
	tmp = smulv2f(src.speed,*basevec);
	if(src.rect.x+(int)tmp.x<=0)
	{
		*basevec = smulxv2f(-1.f, *basevec);
		tmp = smulv2f(src.speed,*basevec);
	}	
	if(src.rect.x+(int)tmp.x>=getWindowWidth()-ZMB_SIZE) // TODO Change dynamic size!!
	{	
		*basevec = smulxv2f(-1.f, *basevec);
		tmp = smulv2f(src.speed,*basevec);
	}
	if(src.rect.y+(int)tmp.y<=0)
	{
		*basevec = smulyv2f(-1.f, *basevec);
		tmp = smulv2f(src.speed,*basevec);
	}	
	if(src.rect.y+(int)tmp.y>=getWindowHeight()-ZMB_SIZE) // TODO Change dynamic size!!
	{	
		*basevec = smulyv2f(-1.f, *basevec);
		tmp = smulv2f(src.speed,*basevec);
	}
	tmp = smulv2f(src.speed,*basevec);
	src.rect.x += (int) tmp.x;
	src.rect.y += (int) tmp.y;
	
	return src.rect;
}
