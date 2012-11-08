#ifndef VECTOR_H
#define VECTOR_H

#ifndef MATH_H
	#define MATH_H
	#include <math.h>
#endif
#ifndef MALLOC_H
	#define MALLOC_H
	#include <malloc.h>
#endif
	#include "types.h"

// floating point 2D vectors
vec2f *mv2f(void);
vec2f v2f(float x1, float y1, float x2, float y2);
vec2f addv2f(vec2f a, vec2f b);
vec2f subv2f(vec2f a, vec2f b);
vec2f smulv2f(float s, vec2f a);
vec2f saddv2f(float s, vec2f a);
vec2f sdivv2f(float s, vec2f a);
float mulv2f(vec2f a, vec2f b);
float lengthv2f(vec2f a);
vec2f basicv2f(vec2f a);
vec2f genStartBaseVec(float x);
vec2f smulxv2f(float s, vec2f a);
vec2f smulyv2f(float s, vec2f a);

vec2f getVector(int angle);
void setVector(vec2f *v, int angle);

#endif