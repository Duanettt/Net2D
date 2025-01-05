#pragma once
#include "Tileset.h"
class Tilemap
{
public:

	Tilemap(Tileset* ts, int width, int height);

	int get_tile(int x, int y);
	int set_tile(int x, int y, int tileIndex);

	// implement editor tools such as filling in a rectangle
	void clear_tile(int x, int y);

	int get_width() { return mapWidth; }
	int get_height() { return mapHeight; }

private:
	std::vector<std::vector<int>> mapData;

	Tileset* tileset;
	int mapWidth;
	int mapHeight;

};

