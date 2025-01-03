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

class Renderer
{
public:
	Renderer() = default;

	void setup_renderer();
	void setup_quad_renderer();
	void setup_shaders();
	void setup_textures();
	void draw();

private:
	unsigned int VAO, VBO;

};

