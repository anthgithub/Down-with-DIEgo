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
		float tempx = x + velx*dt;
		float tempy = y + vely*dt;
		int xdir = velx > 0 ? 1 : 0; // get sign using ternary operator
		int ydir = vely > 0 ? 0 : 1; // get sign using ternary operator
		velx *= 0.995;
		if(world->tiles[int(tempx + xdir) + int(tempy + ydir) * 20]!=0)//Checks for collision in the first quadrant
		{
			velx = 0;
			//tempx = xdir ? floor(tempx + xdir) : ceil(tempx + xdir);
		}
		else if(world->tiles[int(tempx + xdir) + int(tempy + 1 - ydir) * 20] != 0)//Checks the second quadrant
		{
			velx = 0;
			//tempx = xdir ? floor(tempx + xdir) : ceil(tempx + xdir);
		}
		if(world->tiles[int(tempx + 1 - xdir) + int(tempy + 1 - ydir) * 20]!=0)//Checks for collision in the third quadrant
		{
			vely = 0;
			tempy = ydir ? ceil(tempy) : floor(tempy);
		}
		else if(world->tiles[int(tempx + xdir)+int(tempy + 1 - ydir) * 20] != 0)//Checked the x component of the first quadrant
		{
			vely = 0;
			tempy = ydir ? ceil(tempy) : floor(tempy);
		}
		else
		{
			vely += 4.9*dt;
		}

		x = tempx;
		y = tempy;
	}
};
#endif