#pragma once
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

class Texture {
private:
    unsigned int texture;
    int width;
    int height;
    int nrChannels;

public:
    explicit Texture(const char* texture_path);
    unsigned int get_texture() const;
    int get_width() const;
    int get_height() const;
    int get_channels() const;
};