#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Tilesets/Tileset.h"

class Quad
{
public:
	
	void init();
	void setup_quad_data();
	void setup_textures(Tileset* tileset);
	void draw();
private:

	Tileset* currentQuadTileset;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO, VBO, EBO;
};

