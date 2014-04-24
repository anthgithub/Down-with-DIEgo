#include"SDL\SDL.h"
#include"Player.h"

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

void drawMap(int*tileData,SDL_Surface *sprite,SDL_Surface *screen)
{
	SDL_Rect src, dest;

	src.w = TILESIZE;
	src.h = TILESIZE;
	src.y = 0;
	dest.w = TILESIZE;
	dest.h = TILESIZE;

	for(int i = 0; i < 15; i++)
	{
		for(int j = 0; j < 20; j++)
		{
			int type = tileData[i* 20 + j];
			src.x = TILESIZE * type;
			
			dest.x = TILESIZE * j;
			dest.y = TILESIZE * i;

			SDL_BlitSurface(sprite, &src, screen, &dest);
		}
	}

}
int main (int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *gameWindow = SDL_CreateWindow("Down with DIEgo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Surface *screen = SDL_GetWindowSurface(gameWindow);
	player *peterG = new player();
	peterG->sprite = SDL_LoadBMP("MMSprite.bmp");
	peterG->screen = screen;
	int lastTime = SDL_GetTicks();

	while(true)
	{
		int currTime = SDL_GetTicks();
		peterG->update((currTime - lastTime) / 1000.0f);
		peterG->draw();
		SDL_UpdateWindowSurface(gameWindow);
		gameLoop();
		lastTime = currTime;
	}

	return 0;
}