#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Class to one day hopefully get working but rn it just doesnt wanna work.. oop isnt great with opengl.
struct VBO
{
	void init();
	void bind();
	void setup(void* vertices);
private:
	unsigned int VBO;

};

