#ifndef PLAYER_H
#define PLAYER_H
#include "Object.h"
class player : public object
{
public:

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
		x = tempx;
		y = tempy;
	}
};
#endif