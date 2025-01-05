#include "Renderer.h"

void Renderer::setup_renderer()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    quad.init();
    quad.setup_quad_data();
    setup_textures();

    quad.setup_textures(tileset);
}

void Renderer::setup_quad_renderer()
{
    // Soon this will be used for texture data so we will separate it to a texture class or sprite class.
    float vertices[] = {
        // Position     // Texture coords
        0.5f, 0.5f,    1.0f, 1.0f,   // Top right
        0.5f, -0.5f,    1.0f, 0.0f,   // bottom right
        -0.5, -0.5f,    0.0f, 0.0f,   // Bottom left
        -0.5f, 0.5f,    0.0f, 1.0f    // top left
    };

    unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
    };


    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //vbo.setup(vertices);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


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

void Renderer::setup_textures()
{
    ResourceManager& rm = ResourceManager::get_instance();

    rm.load_textures("texture1", "res/Texture/TX Tileset Grass.png");

    Texture* texture1 = rm.get_texture("texture1");
    // Hate dynamically allocating stuff might have to find a way not to..
    tileset = new Tileset(texture1, 32, 32);

}

void Renderer::drawTile(int tileIndex, const glm::vec2& position, const glm::vec2& size) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ResourceManager& rm = ResourceManager::get_instance();
    Shader* spriteShader = rm.get_shaders("sprite");
    spriteShader->use();

    // Calculate model matrix for position and size
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::translate(model, glm::vec3(1.0f));
    //model = glm::scale(model, glm::vec3(size, 1.0f));
    spriteShader->setMat4("model", model);

    // Get tile UV coordinates
    const Tile& tile = tileset->get_tile(4);
    spriteShader->setVec2("textureOffset", tile.textureOffset);
    spriteShader->setVec2("tileSize", tile.tileSize);

    // Correct order: Bind VAO first, then texture, then draw
    //glBindVertexArray(VAO);
    //glBindTexture(GL_TEXTURE_2D, tileset->get_texture()->get_texture());
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);

    quad.draw();
}

void Renderer::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ResourceManager& rm = ResourceManager::get_instance();
    Shader* spriteShader = rm.get_shaders("sprite");
    spriteShader->use();

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    spriteShader->setMat4("model", modelMatrix);

    quad.draw();
}