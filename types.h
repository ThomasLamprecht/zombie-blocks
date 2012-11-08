#ifndef TYPES_H
#define TYPES_H

#include "config.h"
#ifndef SDL_H
	#define SDL_H
	#include <SDL/SDL.h>
#endif
typedef SDL_Rect zbox;

typedef struct _vec2f
{
	float x,y;
} vec2f;

/*typedef struct _vec2d
{
	int x,y;
} vec2d; */

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
	zbox rect;
  vec2f direction;
	float speed;
  uint8_t TYPE;
} zombie;

#endif