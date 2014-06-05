#ifndef MAP_H
#define MAP_H
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include"SDL/SDL.h"
#include"SDL/SDL_image.h"
#include "Object.h"

class map
{
public:
	int *tiles;
	int mh;
	int mw;
	SDL_Surface *sprite;
	SDL_Surface *screen;

	void load(std::string fname)
	{
		mh=40;
		mw=30;
		tiles = new int [mh*mw];
		for(int i = 0; i < mh*mw; i++)
		{
			tiles[i] = 0;
		}
		std::string line;
		std::ifstream myfile (fname);			//Text file
		if (myfile.is_open())					//Open file
		{
			int numLines = 0;
			while (line.compare("data="))		//Read file line by line
			{
				getline(myfile,line);
			}

			while (getline(myfile,line))		//Read file line by line
			{
					int l = line.length() < mw ? line.length() : mw;

					std::istringstream row(line);

					for (int i = 0; i < l; i++)
					{
						getline(row, line, ',') ;
						int result = std::stoi(line);
						tiles[numLines*mw + i] = result;
					}
					numLines++;
			}
			myfile.close();                     //Close file
		}
	}

	void draw(float ox = 0.0f, float oy = 0.0f)
	{
		SDL_Rect src, dest;
		src.w = TILESIZE;
		src.h = TILESIZE;
		src.y = 0;
		dest.w = TILESIZE;
		dest.h = TILESIZE;

		for(int i = 0; i < mh; i++)
		{
			for(int j = 0; j < mw; j++)
			{
				int type = tiles[(i * mw) + j];
				src.x = TILESIZE * type;

				dest.x = TILESIZE * (j + ox);
				dest.y = TILESIZE * (i + oy);

				if(dest.y > screen->h || dest.y < -TILESIZE)
				{
					break;
				}

				if(dest.x < screen->h || dest.y > -TILESIZE)
				{
					SDL_BlitSurface(sprite, &src, screen, &dest);
				}
			}
		}
	}
};
#endif