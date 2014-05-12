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
		int topEdge, botEdge, lEdge, rEdge;

		velx *= 0.99;
		
		if(world->tiles[int(tempx)+int(tempy)*20]!=0)//We are checking if the approaching tile is occupied
		{
			velx = 0;
			vely = 0;
		}
		if(world->tiles[int(tempx+1)+int(tempy)*20]!=0)//Checks for collision with the right side
		{
			velx = 0;
		}
		if(world->tiles[int(tempx)+int(tempy+1)*20]!=0)//Checks for collision with ground
		{
			x = tempx;
			vely = 0;
		}
		if(world->tiles[int(tempx)+int(tempy-1)*20]!=0)//Checks for collision with the ceiling
		{
			x = tempx;
			vely = 0;
		}
		if(world->tiles[int(tempx)+int(tempy)*20]==0)
		{		
			x = tempx;
			y = tempy;
		}
		
	}
};
#endif