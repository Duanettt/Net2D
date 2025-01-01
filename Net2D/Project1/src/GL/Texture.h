#pragma once

#include <glad/glad.h>
#include "stb_image.h"
#include <iostream>

class Texture
{
public:
	Texture();
	Texture(const char* texture_path);

	void load_texture(const char* texture_path);

private:
	unsigned int texture;
	int width, height, nrChannels;
};

