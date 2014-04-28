#include"SDL/SDL.h"
#include"SDL/SDL_image.h"
#include"Player.h"
#include <string>
#include <fstream>
#include <iostream>

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

void loadmap(int* map, std::string fname)
{
	std::string line;

	std::ifstream myfile (fname);        //Text file

	if (myfile.is_open())                 //Open file
	{
		int numLines = 0;

		while (getline (myfile,line))      //Read file line by line
		{
			int l = line.length() < 20 ? line.length() : 20;

			for (int i = 0; i < l; i++)
			{
				switch(line[i])
				{	
				case '!':
					map[numLines*20 + i] = 0;
					break;
				case 'x':
					map[numLines*20 + i] = 1;   
					break;
				case '*':
					map[numLines*20 + i] = 2;
					break;
				}	
			}
			numLines++;
		}
		myfile.close();                     //Close file
	}
}

void drawMap(int *tileData, SDL_Surface *sprite, SDL_Surface *screen)
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
			int type = tileData[(i * 20) + j];
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
	peterG->sprite = IMG_Load("MMSprite.png");
	peterG->screen = screen;
	int lastTime = SDL_GetTicks();

	int* tehmap = new int [20*15];
	for(int i = 0; i < 20*15; i++)
	{
		tehmap[i] = 0;
	}
	loadmap(tehmap, "map.txt");
	SDL_Surface* tiles = IMG_Load("tile1.bmp");

	while(true)
	{
		int currTime = SDL_GetTicks();
		peterG->update((currTime - lastTime) / 1000.0f);
		drawMap(tehmap, tiles, screen);
		peterG->draw();

		SDL_UpdateWindowSurface(gameWindow);
		gameLoop();
		lastTime = currTime;
	}

	return 0;
}