#include "main.h"

int main(void)
{
	srand(time(NULL));
	//char *sdl_error=NULL;
	int run=1,width=1440,height=960,fps_ms=19;
	unsigned int drawn_frames=0, i=0, eye_left, eye_top, lives = 10;
	float m=0.f;
	Uint32 fps_helper,fps_now,fps_next,hit_helper=0,zombie_start_time,zombie_end_time;
	SDL_Surface *screen;
	SDL_Event event;
	SDL_Rect bg, eye;
	zombie enemy[ZOMBIES], player;
	Uint8 *keys;
	
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
	player.speed = 5.f;
	
	for(i=0;i<ZOMBIES;i++)
	{
		enemy[i].rect.w = SQR_SIZE;
		enemy[i].rect.h = SQR_SIZE;	
		enemy[i].rect.x = (rand()%2)?rand()%((int)width/3):width-rand()%((int)width/3-SQR_SIZE)+SQR_SIZE;
		enemy[i].rect.y = (rand()%2)?rand()%((int)height/3):height-rand()%((int)height/3-SQR_SIZE)+SQR_SIZE;
		enemy[i].speed = (float) zombie_speed+(float)((rand()%3000)/1001.f);
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
				player.rect.y += (int) player.speed;
			}
		}
		if(keys[SDLK_UP])
		{
			if(player.rect.y-(int)player.speed>=0)
			{
				player.rect.y -= (int)player.speed;
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
			fps_now = SDL_GetTicks();
			if((player.rect.x+SQR_SIZE>enemy[i].rect.x&&player.rect.x<enemy[i].rect.x+SQR_SIZE)&&(player.rect.y+SQR_SIZE>enemy[i].rect.y&&player.rect.y<enemy[i].rect.y+SQR_SIZE)&&hit_helper<fps_now)
			{				
				lives--;
				printf("Lives: %u\n",lives);
				hit_helper = fps_now + 1500;
				player.rect.x = 0;
				player.rect.y = 0;
			}
			enemy[i].rect = calcEnemyPos(enemy[i], player.rect, 5.f);
		}
		if(lives==0)
		{
			run = 0;
			zombie_end_time = SDL_GetTicks();
		}
		// DRAWING <- should be replaced by OpenGL directives ... 
		SDL_FillRect(screen, &bg, SDL_MapRGB(screen->format, 231, 231, 231)); // draw background		
		SDL_FillRect(screen, &player.rect, SDL_MapRGB(screen->format, 255, 255, 0)); // draw player
		eye.x = player.rect.x + eye_left;
		eye.y = player.rect.y + eye_top;
		SDL_FillRect(screen, &eye, SDL_MapRGB(screen->format, 0, 250, 0)); // draw player's left eye
		eye.x += 2*eye_left;
		SDL_FillRect(screen, &eye, SDL_MapRGB(screen->format, 0, 0, 250)); // draw player's right eyes
		for(i=0;i<ZOMBIES;i++)
		{
			SDL_FillRect(screen, &enemy[i].rect, SDL_MapRGB(screen->format, 255, 0, 0)); // draw ZOMBIES
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
		
		
		// FPS Output
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

SDL_Rect calcEnemyPos(zombie enemy, SDL_Rect player, float speed)
{
	vec2f vec = basicv2f(v2f((float)player.x,(float)player.y,(float)enemy.rect.x,(float)enemy.rect.y));
	vec = smulv2f(enemy.speed,vec);
	enemy.rect.x -= (int) vec.x;
	enemy.rect.y -= (int) vec.y;
	enemy.rect.w = enemy.rect.h = SQR_SIZE;
	return enemy.rect;
}
