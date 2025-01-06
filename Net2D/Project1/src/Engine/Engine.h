// Engine.h
#pragma once
#include "../Core/Window.h"
#include "../Graphics/Renderer.h"
#include "../Globals.h"
#include "../Input/Input.h"
#include "../Tilesets/Tilemap.h"

class Engine
{
public:
    Engine(Engine const&) = delete;
    void operator=(Engine const&) = delete;
    static Engine& get_instance();
    void update();
    void process_input();
    bool is_running() const;
    void init();
    void init(int screenWidth, int screenHeight, const char* title);
    void setup_renders();
    void run();

private:
    KeyInput movementKeys;     // WASD movement
    KeyInput editorKeys;       // Editor controls
    std::unique_ptr<Window> window;
    std::unique_ptr<Tilemap> currentMap;
    Cursor* cursor;
    bool editorMode;
    int currentTileIndex;

    // Private functions for editor
    void process_editor_input();
    void render_editor();
    void init_editor();

    Engine()
        : window(nullptr)
        , cursor(nullptr)
        , currentMap(nullptr)
        , editorMode(false)
        , currentTileIndex(0)
        , movementKeys({ GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D })
        , editorKeys({
            GLFW_KEY_E,           // Toggle editor
            GLFW_KEY_LEFT,        // Previous tile
            GLFW_KEY_RIGHT,       // Next tile
            GLFW_KEY_DELETE       // Clear tile
            })
    {
        globals.r = new Renderer();
    }

    ~Engine()
    {
        delete cursor;
    }
};