#ifndef CFG_H
#define CFG_H

#define GFX_SDL
// #define GFX_OPENGL
/*#ifdef GFX_SDL GFX_OPENGL
	#error "Couldn't compile with SDL _and_ OpenGL flag defined!"
#endif*/

//#define DEBUG 1
#define ZOMBIES 50 // number of zombies
#define RANGE 180
#define RAGE_RANGE 250
#define PLAYER_T 0
#define ZOMBIE_T 1
#define CIVILIAN_T 2
//NOTE! right now all size constants should be the same
#define SQR_SIZE 10 // <- depreceated
#define P_SIZE 10
#define ZMB_SIZE 10

static int getWindowWidth() //NOTE! Not atomar
{
  return 1336;
}
static int getWindowHeight() //NOTE! Not atomar
{
  return 700;
}
static int getFramems()
{
  return 10;
}
#endif