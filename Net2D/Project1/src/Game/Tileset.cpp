#include "Tileset.h"

Tileset::Tileset(Texture* texture, int width, int height) : tilesetTexture(texture), tileWidth(width), tileHeight(height)
{
	rows = texture->get_height() / tileHeight;
	columns = texture->get_width() / tileWidth;


	float tileU = tileHeight / texture->get_height();
	float tileV = tileWidth / texture->get_width();


	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
		{
			Tile tile;
			// Basically due to the fact opengl 0,0 starts at the bottom left we gotta flip something so... yeah...
			tile.textureOffset = glm::vec2(i * tileU, (rows - 1 - j) * tileV);
			tile.tileSize = glm::vec2(tileU, tileV);
			tiles.push_back(tile);
		}
}


