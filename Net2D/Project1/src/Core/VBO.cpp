#include "VBO.h"

void VBO::init()
{
	glGenBuffers(1, &VBO);
}

void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void VBO::setup(void* vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}
