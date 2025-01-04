#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "../GL/Shader.h"
#include "../Core/ResourceManager.h"
#include "../Game/Tileset.h"

class Renderer
{
public:
	Renderer() = default;

	void setup_renderer();
	void setup_quad_renderer();
	void setup_shaders();
	void setup_textures();

	void drawTile(int tileIndex, const glm::vec2& position, const glm::vec2& size);
	void draw();

private:
	Tileset* tileset;
	unsigned int VAO, VBO, EBO;

};

