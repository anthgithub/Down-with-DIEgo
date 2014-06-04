#ifndef OBJECT_H
#define OBJECT_H
#include "SDL\SDL.h"
#include "Player.h"
#define TILESIZE 32
class object
{
public:

	float x, y, velx, vely;
	int w, h;
	SDL_Surface *sprite, *screen;

	object()
	{
		x = 0;
		y = 0;
		velx = 0;
		vely = 0;
		w = 1;
		h = 1;
	}

	object(float nx, float ny, int nw = 1, int nh = 1)
	{
		x = nx;
		y = ny;
		velx = 0;
		vely = 0;
		w = nw;
		h = nh;
	}

	~object()
	{
	}

	void draw(float ox = 0.0f, float oy = 0.0f)
	{
		SDL_Rect src, dest;
		src.x = 0;
		src.y = 0;
		src.w = w*TILESIZE;
		src.h = h*TILESIZE;
		dest.x = (ox + x)*TILESIZE;
		dest.y = (oy + y)*TILESIZE;
		dest.w = w*TILESIZE;
		dest.h = h*TILESIZE;
		SDL_BlitSurface(sprite, &src, screen, &dest);
	}
	virtual void update(float dt)
	{
		vely += 4.9*dt;
		float tempx = x+velx*dt;
		float tempy = y+vely*dt;
		x = tempx;
		y = tempy;
	}
};
#endif