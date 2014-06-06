#ifndef PLAYER_H
#define PLAYER_H
#include "Object.h"
#include "map.h"
class player : public object
{
public:

	static float px, py;

	map* world;

	player() : object()
	{
		x = 10;
		y = 7;
	}

	player(float nx, float ny, int nw = 1, int nh = 1) : object (nx, ny, nw, nh)
	{
		x = 10;
		y = 7;
	}

	~player()
	{
	}

	void jump()
	{
		if(vely == 0)
		{
			vely -= 10;
		}
	}

	bool placeMeeting(float x, float y)
	{

		return	world->tiles[int(x + 0.25f) + int(y) * 30] != 0 ||
				world->tiles[int(x + 0.75f) + int(y + 0.97f) * 30] != 0 ||
				world->tiles[int(x + 0.75f) + int(y) * 30] != 0 ||
				world->tiles[int(x + 0.25f) + int(y + 0.97f) * 30] != 0;
	}

	float sign(float n)
	{
		if(n > 0)
		{
			return 1.0f;
		}
		else if(n < 0)
		{
			return -1.0f;
		}
		else
		{
			return 0.0f;
		}
	}

	void incrementFrame(float dt)
	{
		static float accum = 0;

		accum += dt;

		if(accum > 0.125f)
		{
			frame++;
			accum = 0.0f;

			if(frame > 5)
			{
				frame = 0;
			}
		}
	}

	void update(float dt)
	{
		incrementFrame(dt);

		velx *= 0.965;
		vely += 20*dt; //gravity

		if (velx > 12) //speed cap
		{
			velx = 12;
		}
		if (velx <-12)
		{
			velx = -12;
		}

		float tempx = px + velx * dt;//The player's temporary X
		float tempy = py + vely * dt;//The player's temporary y

		if(placeMeeting(tempx, py))
		{
			while(!placeMeeting(px + sign(velx), py))
			{
				px += sign(velx);
			}
			velx = 0;
		}
		px += velx * dt;

		if(placeMeeting(px, tempy))
		{
			while(!placeMeeting(px, py + sign(vely)))
			{
				py += sign(vely);
			}
			vely = 0;
		}
		py += vely * dt;
	}
};
#endif