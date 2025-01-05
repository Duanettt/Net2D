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
    const Tile& get_tile(int index) const {
        return tiles[index];
    }

    // Get a specific tile by row and column
    const Tile& get_tile(int row, int col) const {
        return tiles[row * columns + col];
    }

    int get_tile_width() const { return tileWidth; }
    int get_tile_height() const { return tileHeight; }
    int get_columns() const { return columns; }
    int get_rows() const { return rows; }

    Texture* get_texture() const { return tilesetTexture; }

private:
	Texture* tilesetTexture;
	int tileWidth;
	int tileHeight;
    int rows;
    int columns;
	std::vector<Tile> tiles;


};

