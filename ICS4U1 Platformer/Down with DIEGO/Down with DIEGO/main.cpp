#include"SDL/SDL.h"
#include"SDL/SDL_image.h"
#include"Player.h"
#include"map.h"

void gameLoop()
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
}


int main (int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *gameWindow = SDL_CreateWindow("Down with DIEgo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Surface *screen = SDL_GetWindowSurface(gameWindow);
	player *peterG = new player();
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
		gameLoop();
		lastTime = currTime;
	}

	return 0;
}