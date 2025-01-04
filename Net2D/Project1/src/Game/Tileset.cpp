#include "Tileset.h"

Tileset::Tileset(Texture* texture, int width, int height) : tilesetTexture(texture), tileWidth(width), tileHeight(height)
{
    rows = texture->get_height() / tileHeight;
    columns = texture->get_width() / tileWidth;

    // Calculate UV size per tile
    float tileU = (float)tileWidth / texture->get_width();   // horizontal
    float tileV = (float)tileHeight / texture->get_height(); // vertical

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            Tile tile;
            // Calculate UV offset for this tile
            tile.textureOffset = glm::vec2(
                x * tileU,                // U offset (horizontal)
                (rows - 1 - y) * tileV    // V offset (vertical)
            );
            tile.tileSize = glm::vec2(tileU, tileV);
            tiles.push_back(tile);
        }
    }
}

