#pragma once
#include "Tilemap.h"
#include "../Core/Window.h"
#include "../Graphics/Renderer.h"
#include "../Globals.h"
#include "../Input/Input.h"

class TileMapEditor
{
public:
	TileMapEditor(Tilemap* mp, Tileset* ts, glm::vec2 cs);

	void handle_input(GLFWwindow* window, double mouseX, double mouseY);

	void set_current_tile(int tileIndex);

	void setup_grid();

	void draw_grid();

	void render();


	void process_editor_input();

private:
	KeyInput editorKeys;        // Largest object, likely 8 bytes or more
	glm::vec2 gridSize;         // 8 bytes
	Tilemap* map;               // 8 bytes
	Tileset* tileset;           // 8 bytes
	int currentTile;            // 4 bytes
	int currentTileIndex = 0;      // 4 bytes;
	int numGridLines = 0;
	unsigned int gridVAO = 0;
	unsigned int gridVBO = 0;
	bool isEditing;             // 1 byte
	bool editorMode;            // 1 byte
};

