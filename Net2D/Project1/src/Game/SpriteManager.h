#pragma once
#include "../Core/ResourceManager.h"
#include "../Tilesets/Tileset.h"
#include "Sprite.h"

class SpriteManager {
public:
    static SpriteManager& get_instance() {
        static SpriteManager instance;
        return instance;
    }

    void init(float screenWidth, float screenHeight) {
        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;

    }

    void draw_sprite(const std::string& textureName, Sprite& sprite) {
        ResourceManager& rm = ResourceManager::get_instance();
        Texture* texture = rm.get_texture(textureName);
        Shader* shader = rm.get_shaders("sprite");

        if (!texture || !shader) return;

        sprite.set_texture(texture);
        sprite.draw(shader, screenWidth, screenHeight);
    }

private:
    SpriteManager() = default;
    float screenWidth = 800.0f;
    float screenHeight = 600.0f;
};