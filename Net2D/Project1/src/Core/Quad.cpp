#include "Quad.h"

void Quad::init()
{
    vertices = {
       // Position     // Texture coords
        0.5f, 0.5f,    1.0f, 1.0f,   // Top right
        0.5f, -0.5f,    1.0f, 0.0f,   // bottom right
        -0.5, -0.5f,    0.0f, 0.0f,   // Bottom left
        -0.5f, 0.5f,    0.0f, 1.0f    // top left
    };

    indices = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
    };
}

void Quad::setup_quad_data()
{
    // Soon this will be used for texture data so we will separate it to a texture class or sprite class.

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    //vbo.setup(vertices);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);


    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Quad::setup_textures(Tileset* tileset)
{
    currentQuadTileset = tileset;
}



void Quad::draw()
{
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, currentQuadTileset->get_texture()->get_texture());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
