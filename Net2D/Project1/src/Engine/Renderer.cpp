#include "Renderer.h"

void Renderer::setup_renderer()
{
    // Soon this will be used for texture data so we will separate it to a texture class or sprite class.
    float vertices[] = {
        // Position     // Texture coords
        0.0f, 1.0f,    0.0f, 1.0f,   // Top left
        1.0f, 1.0f,    1.0f, 1.0f,   // Top right
        0.0f, 0.0f,    0.0f, 0.0f,   // Bottom left
        1.0f, 0.0f,    1.0f, 0.0f    // Bottom right
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Renderer::setup_shaders()
{
    // Get a resource manager using singleton design pattern to load up our shaders
    ResourceManager& rm = ResourceManager::get_instance();
    rm.load_shaders("sprite", "res/shaders/sprite_shader.vert", "res/shaders/sprite_shader.frag");

}

void Renderer::draw()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ResourceManager& rm = ResourceManager::get_instance();
    Shader* spriteShader = rm.get_shaders("sprite");

    spriteShader->use();
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    spriteShader->setMat4("model", modelMatrix);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
