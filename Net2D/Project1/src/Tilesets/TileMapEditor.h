#pragma once
#include "Tilemap.h"
#include "../Core/Window.h"
#include "../Engine/Renderer.h"

class TileMapEditor
{
public:
	TileMapEditor(Tilemap* mp, Tileset* ts, glm::vec2 cs);

	void handle_input(GLFWwindow* window, double mouseX, double mouseY);

	void set_current_tile(int tileIndex);

	void draw_grid(Renderer& renderer);

	void render(Renderer& renderer);

private:
	Tilemap* map;
	Tileset* tileset;
	int currentTile;
	bool isEditing;
	glm::vec2 gridSize;

};

