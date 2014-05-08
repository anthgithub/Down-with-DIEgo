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
		tiles = new int [20*15];
		for(int i = 0; i < 20*15; i++)
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
					int l = line.length() < 20 ? line.length() : 20;

					std::istringstream row(line);

					for (int i = 0; i < l; i++)
					{
						getline(row, line, ',') ;
						int result = std::stoi(line);
						tiles[numLines*20 + i] = result;
					}
					numLines++;
			}
			myfile.close();                     //Close file
		}
	}

	void draw()
	{
		SDL_Rect src, dest;
		src.w = TILESIZE;
		src.h = TILESIZE;
		src.y = 0;
		dest.w = TILESIZE;
		dest.h = TILESIZE;
		for(int i = 0; i < 15; i++)
		{
			for(int j = 0; j < 20; j++)
			{
				int type = tiles[(i * 20) + j];
				src.x = TILESIZE * type;

				dest.x = TILESIZE * j;
				dest.y = TILESIZE * i;

				SDL_BlitSurface(sprite, &src, screen, &dest);
			}
		}\
	}
};
#endif