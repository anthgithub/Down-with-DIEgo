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
		float tempx = x+velx*dt;
		float tempy = y+vely*dt;
		vely += 4.9*dt;
		velx *= 0.995;
		if(world->tiles[int(tempx+1)+int(tempy)*20]!=0)//Checks for collision with the right side
		{
			velx = 0;
		}
		if(world->tiles[int(tempx)+int(tempy)*20]!=0)//Checks for collision with the left side
		{
			velx = 0;
		}
		if(world->tiles[int(tempx)+int(tempy+1)*20]!=0)//Checks for collision with ground
		{
			x = tempx;
			vely = 0;
		}
		if(world->tiles[int(tempx)+int(tempy)*20]==0)//If the tile is free the player can move
		{		
			x = tempx;
			y = tempy;
		}
	}
};
#endif