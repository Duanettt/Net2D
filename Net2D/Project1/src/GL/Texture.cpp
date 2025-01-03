#include "Texture.h"

Texture::Texture(const char* texture_path) {
    // Generate texture ID
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Flip texture vertically (since OpenGL expects different coordinates)
    stbi_set_flip_vertically_on_load(true);

    // Load texture data
    unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        GLenum internalFormat;

        // Determine format based on number of channels
        if (nrChannels == 4) {
            format = GL_RGBA;
            internalFormat = GL_RGBA;
        }
        else if (nrChannels == 3) {
            format = GL_RGB;
            internalFormat = GL_RGB;
        }
        else {
            std::cout << "Unsupported texture format: " << nrChannels << " channels" << std::endl;
            stbi_image_free(data);
            return;
        }

        // Generate the texture
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        std::cout << "Texture loaded successfully: " << texture_path
            << " (" << width << "x" << height
            << ", " << nrChannels << " channels)" << std::endl;
    }
    else {
        std::cout << "Failed to load texture: " << texture_path << std::endl;
    }

    stbi_image_free(data);
}

unsigned int Texture::get_texture() const {
    return texture;
}

int Texture::get_width() const {
    return width;
}

int Texture::get_height() const {
    return height;
}

int Texture::get_channels() const {
    return nrChannels;
}