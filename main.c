#include "main.h"

int main(void)
{
	srand(time(NULL));
	//char *sdl_error=NULL;
  int run=1;
  int width=getWindowWidth(), height=getWindowHeight(), fps_ms=getFramems();
	unsigned int drawn_frames=0, i=0, eye_left, eye_top, lives = 10;
	float m=0.f;
	Uint32 fps_helper,fps_now,fps_next,hit_helper=0,zombie_start_time,zombie_end_time;
	SDL_Surface *screen;
	SDL_Event event;
	SDL_Rect bg, eye;
	zombie enemy[ZOMBIES], player;
	vec2f enemy_random_movement[ZOMBIES];
	Uint8 *keys;
  SDL_Rect **modes;

 /* modes = SDL_ListModes(NULL, SDL_HWSURFACE | SDL_DOUBLEBUF);
  
   Check is there are any modes available
  if(modes == (SDL_Rect **)0){
    printf("No modes available!\n");
    exit(-1);
  }
     Print valid modes 
    printf("Available Modes\n");
    for(i=0;modes[i];++i)
      printf("  %d x %d\n", modes[i]->w, modes[i]->h); */
  
	if(SDL_Init(SDL_INIT_VIDEO)==-1)
	{
		printf("Fehler, SDL konnte nicht initialisiert werden: %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}
	
	bg.x = 0;
	bg.y = 0;
	bg.w = width;
	bg.h = height;
	
	eye.w = (int)SQR_SIZE/5;
	eye.h = (int)SQR_SIZE/4;
	eye_left = eye.w;
	eye_top = eye.h;
	
	screen = window(width,height,32,SDL_HWSURFACE | SDL_DOUBLEBUF,"Zombie Blocks - http://gamer-source.org","Zombie Blocks"); // Fenster initalisieren

	player.rect.w = SQR_SIZE;
	player.rect.h = SQR_SIZE;	
	player.rect.x = (int) width/2-(int)player.rect.w/2;
	player.rect.y = (int) height/2-(int)player.rect.h/2;
	player.speed = PLAYER_SPEED;
	
	for(i=0;i<ZOMBIES;i++)
	{
		enemy[i].rect.w = P_SIZE;
		enemy[i].rect.h = P_SIZE;	
		enemy[i].rect.x = (rand()%2)?rand()%((int)width/3):width-rand()%((int)width/3-SQR_SIZE)+SQR_SIZE;
		enemy[i].rect.y = (rand()%2)?rand()%((int)height/3):height-rand()%((int)height/3-SQR_SIZE)+SQR_SIZE;
		enemy[i].speed = (float) ZOMBIE_SPEED+(float)((rand()%3000)/1001.f);
		enemy_random_movement[i] = genStartBaseVec((rand()%5000)/5000.f);
	}
	
	zombie_start_time = SDL_GetTicks();
	fps_helper = zombie_start_time+5000;
	fps_next = zombie_start_time+fps_ms;
	// MAIN LOOP
	while(run)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
				{
					run=0;
					zombie_end_time = SDL_GetTicks();
					break;
				}
				case SDL_KEYDOWN:
				{
					if(event.key.keysym.sym==SDLK_ESCAPE)
					{
						run=0;
						zombie_end_time = SDL_GetTicks();
					}
					break;
				}
			}
		}
		keys = SDL_GetKeyState(NULL);
		if(keys[SDLK_DOWN])
		{			
			if(player.rect.y+player.rect.h+(int)player.speed<=height)
			{
				player.rect.y += (int) player.speed/((keys[SDLK_RIGHT] || keys[SDLK_LEFT])?1.6f:1);
			}
		}
		if(keys[SDLK_UP])
		{
			if(player.rect.y-(int)player.speed>=0)
			{
				player.rect.y -= (int)player.speed/((keys[SDLK_RIGHT] || keys[SDLK_LEFT])?1.6f:1);
			}
		}
		if(keys[SDLK_RIGHT])
		{
			if(player.rect.x+(int)player.speed+player.rect.w<=width)
			{
				player.rect.x += (int)player.speed;
			}
		}
		if(keys[SDLK_LEFT])
		{			
			if(player.rect.x-(int)player.speed>=0)
			{
				player.rect.x -= (int)player.speed;
			}
		}
		// GAME LOGIC
		//fps_now = SDL_GetTicks();
		for(i=0;i<ZOMBIES;i++)
		{		
			if(collideBoxes(player.rect, enemy[i].rect) && hit_helper<(fps_now = SDL_GetTicks()))
			{				
				lives--;
				printf("Lives: %u\n",lives);
				hit_helper = fps_now + 2000;
				player.rect.x = 0;
				player.rect.y = 0;
			}
			isInRange(enemy[i].rect, player.rect, 50);
			enemy[i].rect = calcEnemyPosRanged(enemy[i], player.rect, RANGE, &enemy_random_movement[i]);
		}
		if(lives==0)
		{
			run = 0;
			zombie_end_time = SDL_GetTicks();
		}
		// DRAWING <- should be replaced by OpenGL directives ... 
		SDL_FillRect(screen, &bg, SDL_MapRGB(screen->format, 151, 151, 151)); // draw background
#ifdef DEBUG
		for(i=0;i<ZOMBIES;i++)
		{
			SDL_Rect tmp_rect;
			tmp_rect.x = enemy[i].rect.x-RANGE+ZMB_SIZE/2;
			tmp_rect.y = enemy[i].rect.y-RANGE+ZMB_SIZE/2;
			tmp_rect.w = 2*RANGE;
			tmp_rect.h = tmp_rect.w;
			SDL_FillRect(screen, &tmp_rect, SDL_MapRGB(screen->format, 0, 100, 255)); // draw range field
		}
#endif	
		SDL_FillRect(screen, &player.rect, SDL_MapRGB(screen->format, 255, 255, 0)); // draw player
		eye.x = player.rect.x + eye_left;
		eye.y = player.rect.y + eye_top;
		SDL_FillRect(screen, &eye, SDL_MapRGB(screen->format, 0, 250, 0)); // draw player's left eye
		eye.x += 2*eye_left;
		SDL_FillRect(screen, &eye, SDL_MapRGB(screen->format, 0, 0, 250)); // draw player's right eyes
		// draw zombies
		for(i=0;i<ZOMBIES;i++)
		{
			SDL_FillRect(screen, &enemy[i].rect, SDL_MapRGB(screen->format, 255, 0, 0)); // draw body
			eye.x = enemy[i].rect.x + eye_left;
			eye.y = enemy[i].rect.y + eye_top;
			SDL_FillRect(screen, &eye, SDL_MapRGB(screen->format, 0, 0, 0)); // draw ZOMBIE's left eye
			eye.x += 2*eye_left;
			SDL_FillRect(screen, &eye, SDL_MapRGB(screen->format, 0, 0, 0)); // draw ZOMBIE's right eye
		}
		SDL_Flip(screen);
		
		/*if((sdl_error=SDL_GetError())!=NULL)
		{
			printf("Error occured:: %s\n",sdl_error);
		}*/
		
		
		// FPS output
		drawn_frames++;
		if(fps_helper<(fps_now = SDL_GetTicks()))
		{
			printf("%d Frames after %.3f Seconds => fps: %.3f\n",drawn_frames,(fps_now-fps_helper+5000)/1000.0f,drawn_frames/((fps_now-fps_helper+5000)/1000.0f));
			fps_helper = fps_now+5000;
			drawn_frames=0;
		}
		fps_now = SDL_GetTicks();
		SDL_Delay((fps_next<=fps_now)?0:fps_next-fps_now);
		fps_next += fps_ms;
	}
	// Quitting game
	printf("You've played %.2f seconds!\n",(float)(zombie_end_time-zombie_start_time)/1000.f);
	SDL_FreeSurface(screen);
	SDL_Quit();
	return 0;
}


SDL_Surface *window(int width, int height, int bpp, Uint32 flags, char *window_title, char *icon_title)
{
	SDL_Surface *screen;
	if((screen = SDL_SetVideoMode(width, height, bpp, flags))==NULL)
	{
		if((screen = SDL_SetVideoMode(width, height, bpp, 0))==NULL)
		{
			printf("Can't set video mode: %s\n", SDL_GetError());
			exit(1);
		}	
	}	
	SDL_WM_SetCaption(window_title,icon_title); // Setzt Titel für das Fenster
	return screen;
}
