#ifndef CONFIG_H
	#define CONFIG_H
	#include "config.h"
#endif
#ifndef SDL_H
	#define SDL_H
	#include <SDL/SDL.h>
#endif
typedef struct _vec2f
{
	float x,y;
} vec2f;

typedef struct _vec2d
{
	int x,y;
} vec2d;

typedef struct _windowNFO
{
	int width, height;
} windowNFO;

typedef struct _gameNFO
{
	int width, height;
} gameNFO;

typedef struct _zombie
{
	SDL_Rect rect;
	float speed;
} zombie;
