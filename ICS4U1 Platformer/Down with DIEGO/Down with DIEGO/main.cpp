#include"SDL/SDL.h"
#include"SDL/SDL_image.h"
#include"SDL/SDL_mixer.h"
#include"Player.h"
#include"Enemy.h"
#include"Missile.h"
#include"map.h"

player *peterG;
enemy *enemy1;
missile *pGMissile;

const Uint8 *keys = SDL_GetKeyboardState(NULL);
SDL_Surface *screen;

Mix_Music *music;
SDL_Window *gameWindow;

float player::px = 0;
float player::py = 0;

void init()
{
	SDL_Init(SDL_INIT_VIDEO);
	gameWindow = SDL_CreateWindow("Down with DIEgo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	screen = SDL_GetWindowSurface(gameWindow);

	music = NULL;
	Mix_Init(MIX_INIT_FLAC);

	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    
}

void gameLoop(float dt)
{
	static int pGMissileCount=0;
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_KEYDOWN:
			if(keys[SDL_SCANCODE_SPACE])
			{
				peterG->jump();
			}
			break;
		case SDL_QUIT:
			exit(0);
			break;
		}
		if(keys[SDL_SCANCODE_X])
		{
			pGMissile[pGMissileCount%5].start(peterG->x,peterG->y);
			pGMissileCount++;
		}
	}
	if(keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT])
	{
		peterG->velx-=256.0*dt;
	}
	if(keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT])
	{
		peterG->velx+=256.0*dt;
	}

	//if(keys[SDLK_UP || SDLK_s])

}


int main (int argc, char** argv)
{
	
	init();
	music = Mix_LoadMUS( "tarkus.flac" );

	peterG = new player();
	peterG->sprite = IMG_Load("HeroAni.png");
	peterG->screen = screen;
	int lastTime = SDL_GetTicks();

	map level1;

	peterG->world = &level1;
	Mix_PlayMusic( music, -1 );
	level1.load("map.txt");
	level1.screen = screen;
	level1.sprite = IMG_Load("tile1.bmp");

	enemy1 = new enemy(1,1,0,true);
	enemy1->sprite = IMG_Load("WalkerAni.png");
	enemy1->screen = screen;
	enemy1->world = &level1;

	pGMissile = new missile [10];
	for(int i = 0; i < 10; i++)
	{
		pGMissile[i] = missile(-1, -1);
		pGMissile[i].screen = screen;
		pGMissile[i].world = &level1;// This loads though, jus cause
	}

	while(true)
	{
		SDL_FillRect(screen, &screen->clip_rect, 0x00A0C0);
		int currTime = SDL_GetTicks();
		peterG->update((currTime - lastTime) / 1000.0f);
		enemy1->update((currTime - lastTime) / 1000.0f,peterG->x);

		level1.draw(10 - player::px, 7 - player::py);
		peterG->draw();
		enemy1->draw(10 - player::px, 7 - player::py);
		for(int i = 0; i < 10; i++)
		{	
			pGMissile[i].update((currTime - lastTime) / 1000.0f);
			pGMissile[i].draw(10 - player::px, 7 - player::py, 0x00FF00FF);
		}
		SDL_UpdateWindowSurface(gameWindow);
		gameLoop((currTime - lastTime) / 1000.0f);
		lastTime = currTime;
	}

	return 0;
}