#include"SDL/SDL.h"
#include"SDL/SDL_image.h"
#include"Player.h"
#include"map.h"

player *peterG;
const Uint8 *keys = SDL_GetKeyboardState(NULL);

void gameLoop(float dt)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_KEYDOWN:
			break;
		case SDL_QUIT:
			exit(0);
			break;
		}
	}
	if(keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT])
	{
		peterG->velx-=6.0*dt;
	}
	if(keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT])
	{
		peterG->velx+=6.0*dt;
	}
	//if(keys[SDLK_DOWN || SDLK_w])

	//if(keys[SDLK_UP || SDLK_s])

}


int main (int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *gameWindow = SDL_CreateWindow("Down with DIEgo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Surface *screen = SDL_GetWindowSurface(gameWindow);
	peterG = new player();
	peterG->sprite = IMG_Load("MMSprite.png");
	peterG->screen = screen;
	int lastTime = SDL_GetTicks();

	map level1;

	peterG->world = &level1;

	level1.load("map.txt");
	level1.screen = screen;
	level1.sprite = IMG_Load("tile1.bmp");
	while(true)
	{
		int currTime = SDL_GetTicks();
		peterG->update((currTime - lastTime) / 1000.0f);
		level1.draw();
		peterG->draw();
		SDL_UpdateWindowSurface(gameWindow);
		gameLoop((currTime - lastTime) / 1000.0f);
		lastTime = currTime;
	}

	return 0;
}