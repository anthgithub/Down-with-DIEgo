#ifndef MISSILE_H
#define MISSILE_H
#include "Object.h"
#include "map.h"

class missile : public object
{
public:
	map* world;

	missile() : object() //default constructor
	{
	}


	missile(float nx, float ny, int nw = 1, int nh = 1) : object (nx, ny, nw, nh) //missile constructor
	{
		x = nx;
		y = ny;
		velx=0;
		vely=0;
	}

	~missile()
	{
	}

	void start(float nx,float ny) // This should place the missile at the location of the object firing.
	{
		x=nx;
		y=ny;
		velx=10;
	}
	void stop() // This should place the missile off-screen.
	{
		x=-1;
		y=-1;
		velx=0;
	}

	void draw(float ox, float oy, Uint32 color) // This draws the missile as a rectangle of chosen colour.
	{
		SDL_Rect dest;
		dest.x = (ox + x)*TILESIZE;
		dest.y = (oy + y)*TILESIZE;
		dest.w = w*TILESIZE;
		dest.h = h*0.25f*TILESIZE;

		SDL_FillRect(screen, &dest, color);
	}

	void update(float dt) // changes missile position and causes missile to stop if conditions are right.
	{
		float tempx = x+velx*dt;
		float tempy = y+vely*dt;

		if(world->tiles[int(tempx) + int(tempy) * 20] != 0 
			|| (world->tiles[(int(tempx)+1) + (int(tempy) * 20)] != 0))//We are checking if the approaching tile is occupied
		{
			stop();
			return;
		}

		x = tempx;
		y = tempy;
	}
};
#endif