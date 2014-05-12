#ifndef MISSILE_H
#define MISSILE_H
#include "Object.h"
#include "map.h"
class missile : public object
{
public:

	map* world;

	missile() : object()
	{
	}

	missile(float nx, float ny, float vx, float vy, int nw = 1, int nh = 1) : object (nx, ny, nw, nh)
	{
		velx=vx;
		vely=vy;
	}

	~missile()
	{
	}

	void update(float dt)
	{
		float tempx = x+velx*dt;
		float tempy = y+vely*dt;
		
		if(world->tiles[int(tempx)+int(tempy)*20]!=0)//We are checking if the approaching tile is occupied
		{
			delete this;//Probably doesn't work; not what we want.
		}
		else
		{		
			x = tempx;
			y = tempy;
		}
	}
};
#endif