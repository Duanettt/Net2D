// Sprite.h
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Core/Quad.h"
#include "../Core/ResourceManager.h"

class Sprite {
public:
    Sprite(const glm::vec2& position = glm::vec2(0.0f), const glm::vec2& size = glm::vec2(32.0f))
        : position(position)
        , size(size)
        , rotation(0.0f)
    {
        currentTexture = ResourceManager::get_instance().get_texture("sprite");
    }

    void init()
    {
        if (!quad.is_init()) {
            quad.init();
            quad.setup_quad_data();
            quad.setup_textures(currentTexture);
        }
    }

    void set_texture(Texture* texture) {
        currentTexture = texture;
    }

    void draw(Shader* shader, float screenWidth, float screenHeight) {
        if (!currentTexture) return;

        // Convert screen coordinates to NDC
        glm::vec2 ndcPos;
        ndcPos.x = (position.x / screenWidth) * 2.0f - 1.0f;
        ndcPos.y = -((position.y / screenHeight) * 2.0f - 1.0f);

        // Convert size to NDC scale
        glm::vec2 ndcSize;
        ndcSize.x = (size.x / screenWidth) * 2.0f;
        ndcSize.y = (size.y / screenHeight) * 2.0f;

        // Create model matrix
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(ndcPos, 0.0f));

        if (rotation != 0.0f) {
            model = glm::translate(model, glm::vec3(ndcSize.x * 0.5f, ndcSize.y * 0.5f, 0.0f));
            model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::translate(model, glm::vec3(-ndcSize.x * 0.5f, -ndcSize.y * 0.5f, 0.0f));
        }

        model = glm::scale(model, glm::vec3(ndcSize, 1.0f));

        // Set shader uniforms
        shader->use();
        shader->setMat4("model", model);

        // Bind texture and draw
        glBindTexture(GL_TEXTURE_2D, currentTexture->get_texture());
        quad.draw();
    }

    // Setters
    void set_position(const glm::vec2& pos) { position = pos; }
    void set_size(const glm::vec2& sz) { size = sz; }
    void set_rotation(float rot) { rotation = rot; }

    // Getters
    const glm::vec2& get_position() const { return position; }
    const glm::vec2& get_size() const { return size; }
    float get_rotation() const { return rotation; }

private:
    static Quad quad;  // Shared quad for all sprites
    Texture* currentTexture = nullptr;
    glm::vec2 position;
    glm::vec2 size;
    float rotation;
};