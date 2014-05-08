#ifndef PLAYER_H
#define PLAYER_H
#include "Object.h"
#include "map.h"
class player : public object
{
public:

	map* world;

	player() : object()
	{
	}

	player(float nx, float ny, int nw = 1, int nh = 1) : object (nx, ny, nw, nh)
	{
	}

	~player()
	{
	}

	void update(float dt)
	{
		vely += 4.9*dt;
		float tempx = x+velx*dt;
		float tempy = y+vely*dt;
		
		if(world->tiles[int(tempx)+int(tempy)*20]!=0)//We are checking if the approaching tile is occupied
		{
			if(tempy + h)
			{

			}
		}
		else
		{		
			x = tempx;
			y = tempy;
		}
	}
};
#endif