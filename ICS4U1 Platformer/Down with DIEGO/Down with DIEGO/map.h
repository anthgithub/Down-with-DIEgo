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

	SDL_Surface *sprite;
	SDL_Surface *screen;

	void load(std::string fname)
	{
		tiles = new int [40*30];
		for(int i = 0; i < 40*30; i++)
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
					int l = line.length() < 30 ? line.length() : 30;

					std::istringstream row(line);

					for (int i = 0; i < l; i++)
					{
						getline(row, line, ',') ;
						int result = std::stoi(line);
						tiles[numLines*30 + i] = result;
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

		for(int i = 0; i < 40; i++)
		{
			for(int j = 0; j < 30; j++)
			{
				int type = tiles[(i * 30) + j];
				src.x = TILESIZE * type;

				dest.x = TILESIZE * (j + ox);
				dest.y = TILESIZE * (i + oy);

				SDL_BlitSurface(sprite, &src, screen, &dest);
			}
		}
	}
};
#endif