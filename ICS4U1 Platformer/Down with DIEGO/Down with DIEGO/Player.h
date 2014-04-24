#ifndef PLAYER_H
#define PLAYER_H
#include "SDL\SDL.h"
#define TILESIZE 32
class player
{
public:
	float x, y, velx, vely;
	int w, h;
	SDL_Surface *sprite, *screen;
	player()
	{
		x = 0;
		y = 0;
		velx = 0;
		vely = 0;
		w = TILESIZE;
		h = TILESIZE;
	}
	void draw()
	{
		SDL_Rect src, dest;
		src.x = 0;
		src.y = 0;
		src.w = w;
		src.h = h;
		dest.x = x*TILESIZE;
		dest.y = y*TILESIZE;
		dest.w = w;
		dest.h = h;
		SDL_BlitSurface(sprite, &src, screen, &dest);
	}
	void update(float dt)
	{
		vely += 4.9*dt;
		float tempx = x+velx*dt;
		float tempy = y+vely*dt;
		x = tempx;
		y = tempy;
	}
};
#endif