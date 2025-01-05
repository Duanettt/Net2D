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
#include "../Core/VBO.h"
#include "../Core/Quad.h"

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
	Quad quad;
	Tileset* tileset;
	unsigned int VAO, EBO;
	unsigned int VBO;

};

