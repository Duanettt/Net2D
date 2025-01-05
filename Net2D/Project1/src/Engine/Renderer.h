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
#include "../Core/VBO.h"
#include "../Core/Quad.h"
#include "../Tilesets/Tileset.h"

class Renderer
{
public:
	Renderer() = default;

	void setup_renderer();
	void setup_quad_renderer();
	void setup_line_renderer(glm::vec2 start, glm::vec2 end, glm::vec4 color);
	void setup_shaders();
	void setup_textures();

	void drawTile(int tileIndex, const glm::vec2& position, const glm::vec2& size);
	void draw();
	void drawLine(glm::vec2 start, glm::vec2 end, glm::vec4 color);

private:
	Quad quad;
	Tileset* tileset;
	unsigned int VAO, EBO;
	unsigned int VBO;

};

