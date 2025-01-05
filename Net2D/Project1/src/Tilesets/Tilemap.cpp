#include "Tilemap.h"

Tilemap::Tilemap(Tileset* ts, int width, int height) : tileset(ts), mapWidth(width), mapHeight(height)
{
	/* so basically we use a nested vector to create a 2d array. We have height as the first parameter which basically indicates each row and then within each row we initialize the columns with -1.
	*/
	mapData.resize(height, std::vector<int>(width, -1));
}

int Tilemap::get_tile(int x, int y)
{
	if (x >= 0 && x <= mapWidth && y >= 0 && y <= mapHeight)
	{
		return mapData[y][x];
	}
}

int Tilemap::set_tile(int x, int y, int tileIndex)
{
	if (x >= 0 && x <= mapWidth && y >= 0 && y <= mapHeight)
	{
		return mapData[y][x] = tileIndex;
	}
}

void Tilemap::clear_tile(int x, int y)
{
	set_tile(x, y, -1);
}


