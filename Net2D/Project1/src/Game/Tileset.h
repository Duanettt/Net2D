#pragma once
#include "../GL/Texture.h"
#include <glm/glm.hpp>
#include <vector>

struct Tile
{
	// Basically tells us how far into our tileset each tile is but in UV coordinates
	glm::vec2 textureOffset;
	// Basically tells us the total size of each tile but in UV coordinates
	glm::vec2 tileSize;
};


class Tileset
{
public:
	Tileset(Texture* texture, int width, int height);

    // Get a specific tile by index
    const Tile& getTile(int index) const {
        return tiles[index];
    }

    // Get a specific tile by row and column
    const Tile& getTile(int row, int col) const {
        return tiles[row * columns + col];
    }

    int getTileWidth() const { return tileWidth; }
    int getTileHeight() const { return tileHeight; }
    int getColumns() const { return columns; }
    int getRows() const { return rows; }

private:
	Texture* tilesetTexture;
	int tileWidth;
	int tileHeight;
    int rows;
    int columns;
	std::vector<Tile> tiles;


};

