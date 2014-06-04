#ifndef ENEMY_H
#define ENEMY_H
#include "Object.h"
#include "map.h"
#define SPEED 3

class enemy : public object
{
public:
	float x1, x2, status;	//rally point (points which the enemy might pace between), and ai status
	map* world;

	enemy() : object()
	{
	}

	enemy(float nx, float ny, float nx2, float nstatus, int nw = 1, int nh = 1) : object (nx, ny, nw, nh)
	{
		velx=SPEED;
		x1=x;			//initial position is left rally point
		x2=nx2;			//extra value is right rally point
		status=nstatus;	//0 is pacer, 1 is chaser.	
	}

	~enemy()
	{
	}
	void jump() //Chaser jump
	{
		if(vely == 0)
		{
			vely -= 5;
		}
	}
	bool placeMeeting(float x, float y)
	{

		return	world->tiles[int(x) + int(y) * 30] != 0 ||
				world->tiles[int(x + 0.97f) + int(y + 0.97f) * 30] != 0 ||
				world->tiles[int(x + 0.97f) + int(y) * 30] != 0 ||
				world->tiles[int(x) + int(y + 0.97f) * 30] != 0;
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

			if(frame > 1)
			{
				frame = 0;
			}
		}
	}
	void update(float dt,float px)
	{
		
		incrementFrame(dt);

		vely += 20*dt; //gravity

		float tempx = x + velx * dt;//The player's temporary X
		float tempy = y + vely * dt;//The player's temporary y

		if(status==1)// causes the enemy to chase and jump if that is its behavior
		{
			velx=(tempx>px) ? -1 : (tempx<px)*SPEED;//gets direction to desired point
			jump();
		}
		else if(status==0)// causes the enemy to pace if not a chaser
		{
			if(tempx<x1)
				velx=SPEED;
			else if(tempx>x2)
				velx=-SPEED;
		}

		if(placeMeeting(tempx, y))
		{
			while(!placeMeeting(y + sign(velx), y))
			{
				tempx += sign(velx);
			}
			velx = 0;
		}
		x += velx * dt;

		if(placeMeeting(x, tempy))
		{
			while(!placeMeeting(x, y + sign(vely)))
			{
				tempy += sign(vely);
			}
			vely = 0;
		}
		y += vely * dt;
	}
};
#endif