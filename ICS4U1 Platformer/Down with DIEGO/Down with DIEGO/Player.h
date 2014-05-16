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
		float tempx = x + velx * dt;
		float tempy = y + vely * dt;
		int xdir = velx > 0 ? 1 : 0; // get sign using ternary operator
		int ydir = vely < 0 ? 1 : 0; // get sign using ternary operator
		velx *= 0.995;
		vely += 4.9*dt;

		bool q1 = world->tiles[int(tempx + xdir) + int(tempy + ydir) * 20] != 0;
		bool q2 = world->tiles[int(tempx + xdir) + int(tempy + 1 - ydir) * 20] != 0;
		bool q3 = world->tiles[int(tempx + 1 - xdir) + int(tempy + 1 - ydir) * 20] != 0;

		if(velx)
		{
			if(q1 || (q2 && !q3)) //Checks for collision in the first quadrant
			{
				tempx = xdir ? floor(tempx) : ceil(tempx);
			}
		}

		if(vely)
		{
			if(q3 || (q2 && !q1))//Checks for collision in the third quadrant
			{
				vely = 0;
				tempy = ydir ? ceil(tempy) : floor(tempy);
			}
		}

		x = tempx;
		y = tempy;
	}
};
#endif