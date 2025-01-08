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
    rm.load_shaders("tiles", "res/shaders/tilesetShader.vert", "res/shaders/tilesetShader.frag");
    rm.load_shaders("sprite", "res/shaders/sprite_shader.vert", "res/shaders/sprite_shader.frag");
    rm.load_shaders("lines", "res/shaders/line_shader.vert", "res/shaders/line_shader.frag");

}

void Renderer::setup_textures()
{
    ResourceManager& rm = ResourceManager::get_instance();

    rm.load_textures("texture1", "res/Texture/TX Tileset Grass.png");
    rm.load_textures("sprite", "res/MaleCharacter/Sword_Idle/Sword_Idle_full.png");
    Texture* texture1 = rm.get_texture("texture1");
    // Hate dynamically allocating stuff might have to find a way not to..
    tileset = new Tileset(texture1, 32, 32);

}

void Renderer::drawTile(int tileIndex, const glm::vec2& position, const glm::vec2& size) {
    ResourceManager& rm = ResourceManager::get_instance();
    Shader* tileShader = rm.get_shaders("tiles");
    tileShader->use();

    //// Convert screen coordinates to normalized device coordinates (NDC)
    float screenWidth = 800.0f;  // Get these from your window
    float screenHeight = 600.0f;

    //// Convert position to NDC (-1 to 1)
    glm::vec2 ndcPos;
    ndcPos.x = (position.x / screenWidth) * 2.0f - 1.0f;
    ndcPos.y = -((position.y / screenHeight) * 2.0f - 1.0f); // Flip Y coordinates

    //// Convert size to NDC scale
    glm::vec2 ndcSize;
    ndcSize.x = (20 / screenWidth) * 2.0f;
    ndcSize.y = (20 / screenHeight) * 2.0f;

    // Calculate model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(ndcPos, 0.0f));
    model = glm::scale(model, glm::vec3(ndcSize, 1.0f));

    tileShader->setMat4("model", model);

    // Set tile UV coordinates
    const Tile& tile = tileset->get_tile(tileIndex);
    tileShader->setVec2("textureOffset", tile.textureOffset);
    tileShader->setVec2("tileSize", tile.tileSize);

    // Correct order: Bind VAO first, then texture, then draw
    //glBindVertexArray(VAO);
    //glBindTexture(GL_TEXTURE_2D, tileset->get_texture()->get_texture());
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0);

    quad.draw();
}

void Renderer::setup_line_renderer(glm::vec2 start, glm::vec2 end, glm::vec4 color)
{
    ResourceManager& rm = ResourceManager::get_instance();

    float vertices[] = {
        start.x, start.y,  // First point
        end.x, end.y       // Second point
    };

    if (lineVAO == 0) {
        glGenVertexArrays(1, &lineVAO);
    }
    if (lineVBO == 0) {
        glGenBuffers(1, &lineVBO);
    }

    glBindVertexArray(lineVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shader* lineShader = rm.get_shaders("lines");
    lineShader->use();
    lineShader->setVec4("color", color);
}
void Renderer::setup_sprite_renderer()
{
    userSprite.init();
    Texture* spriteTexture = ResourceManager::get_instance().get_texture("spriteTexture");
    userSprite.set_texture(spriteTexture);
}

void Renderer::draw_line()
{
    ResourceManager& rm = ResourceManager::get_instance();
    Shader* lineShader = rm.get_shaders("lines");

    lineShader->use();
    glBindVertexArray(lineVAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
}

void Renderer::draw_sprite()
{
    SpriteManager::get_instance().draw_sprite("sprite", userSprite);

}

void Renderer::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ResourceManager& rm = ResourceManager::get_instance();
    Shader* tileShader = rm.get_shaders("tiles");
    tileShader->use();

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    tileShader->setMat4("model", modelMatrix);

    quad.draw();
}