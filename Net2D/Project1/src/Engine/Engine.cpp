#include "Engine.h"

Engine& Engine::get_instance()
{
	static Engine instance;

	return instance;
}


void Engine::update()
{
}

void Engine::init()
{
    window = std::make_unique<Window>(800, 600, "Game");

    window->CreateWindow();
    window->SetCurrentContext();
    window->SetWindowUserPointer(cursor);
    // set mouse call back soon
    //window.SetCallbacks();
    KeyInput::setup_key_inputs(*window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    init_editor();
}

void Engine::init(int screenWidth, int screenHeight, const char* title) 
{   
    window = std::make_unique<Window>(screenWidth, screenHeight, title);
    window->CreateWindow();
    window->SetCurrentContext();
    //window->SetCallbacks();
    window->SetWindowUserPointer(cursor);

    KeyInput::setup_key_inputs(*window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    init_editor();
}

void Engine::setup_renders()
{
    globals.r->setup_shaders();
    globals.r->setup_renderer();
}
void Engine::run()
{

    //r.draw();

    process_input();
    render_editor();  // Add editor rendering

    //globals.r->drawTile(currentTileIndex, glm::vec2(100, 100), glm::vec2(32, 32));


    glfwSwapBuffers(window->GetWindow());
    glfwPollEvents();
}


bool Engine::is_running() const {
    return !glfwWindowShouldClose(window->GetWindow());
}

void Engine::init_editor()
{
    // Create a new tilemap after renderer is set up
    currentMap = std::make_unique<Tilemap>(globals.r->get_tileset(), 20, 20);
}

void Engine::process_input()
{
    if (glfwGetKey(window->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window->GetWindow(), true);

    if (movementKeys.get_is_key_down(GLFW_KEY_W))
    {
        std::cout << "W Key has been pressed!" << std::endl;
    }

    process_editor_input(); // Process editor inputs
}

void Engine::process_editor_input()
{
    // Toggle editor mode
    static bool eKeyWasDown = false;
    bool eKeyIsDown = editorKeys.get_is_key_down(GLFW_KEY_E);
    if (eKeyIsDown && !eKeyWasDown) {
        editorMode = !editorMode;
        std::cout << "Editor mode: " << (editorMode ? "ON" : "OFF") << std::endl;
    }
    eKeyWasDown = eKeyIsDown;

    if (!editorMode || !currentMap) return;

    // Handle tile selection with arrow keys
    static bool leftKeyWasDown = false;
    static bool rightKeyWasDown = false;

    bool leftKeyIsDown = editorKeys.get_is_key_down(GLFW_KEY_LEFT);
    bool rightKeyIsDown = editorKeys.get_is_key_down(GLFW_KEY_RIGHT);



    if (leftKeyIsDown && !leftKeyWasDown) {
        currentTileIndex = std::max(0, currentTileIndex - 1);
        std::cout << "Selected tile: " << currentTileIndex << std::endl;
    }
    if (rightKeyIsDown && !rightKeyWasDown) {
        int maxTiles = globals.r->get_tileset()->get_columns() *
            globals.r->get_tileset()->get_rows() - 1;
        currentTileIndex = std::min(maxTiles, currentTileIndex + 1);
        std::cout << "Selected tile: " << currentTileIndex << std::endl;
    }

    leftKeyWasDown = leftKeyIsDown;
    rightKeyWasDown = rightKeyIsDown;

    // Handle tile placement with mouse
    double mouseX, mouseY;
    glfwGetCursorPos(window->GetWindow(), &mouseX, &mouseY);

    // Convert screen coordinates to grid coordinates
    int tileSize = globals.r->get_tileset()->get_tile_width();
    int gridX = static_cast<int>(mouseX) / tileSize;
    int gridY = static_cast<int>(mouseY) / tileSize;

    // Place or clear tiles
    if (glfwGetMouseButton(window->GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        currentMap->set_tile(gridX, gridY, currentTileIndex);
    }
    if (glfwGetMouseButton(window->GetWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        currentMap->clear_tile(gridX, gridY);
    }
}

void Engine::render_editor()
{
    if (!editorMode || !currentMap) return;

    // Draw all placed tiles
    for (int y = 0; y < currentMap->get_height(); y++) {
        for (int x = 0; x < currentMap->get_width(); x++) {
            int tileIndex = currentMap->get_tile(x, y);
            if (tileIndex >= 0) {
                globals.r->drawTile(
                    tileIndex,
                    glm::vec2(x * globals.r->get_tileset()->get_tile_width(),
                        y * globals.r->get_tileset()->get_tile_height()),
                    glm::vec2(globals.r->get_tileset()->get_tile_width(),
                        globals.r->get_tileset()->get_tile_height())
                );
            }
        }
    }

    // Draw currently selected tile at mouse position (preview)
    double mouseX, mouseY;
    glfwGetCursorPos(window->GetWindow(), &mouseX, &mouseY);

    // Snap preview to grid
    int tileSize = globals.r->get_tileset()->get_tile_width();
    int gridX = static_cast<int>(mouseX) / tileSize * tileSize;
    int gridY = static_cast<int>(mouseY) / tileSize * tileSize;

    globals.r->drawTile(
        currentTileIndex,
        glm::vec2(gridX, gridY),
        glm::vec2(globals.r->get_tileset()->get_tile_width(),
            globals.r->get_tileset()->get_tile_height())
    );
}

