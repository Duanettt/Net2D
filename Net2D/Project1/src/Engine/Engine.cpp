#include "Engine.h"

Engine& Engine::get_instance()
{
	static Engine instance;

	return instance;
}


void Engine::update()
{
    process_editor_input();
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

}

void Engine::setup_renders()
{
    globals.r->setup_shaders();
    globals.r->setup_renderer();
    globals.r->setup_sprite_renderer();

    // Editors will be separated from this soon.
    init_editor();

}
void Engine::run()
{

    //r.draw();

    process_input();
    //render_editor();  // Add editor rendering
    tme->render();

    globals.r->draw_sprite();

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

    // Initialize the TileMapEditor with the current map, tileset, and grid size
    glm::vec2 gridSize(32.0f, 32.0f); // Adjust grid size based on your tile size
    tme = new TileMapEditor(currentMap.get(), globals.r->get_tileset(), gridSize);

    // Set up the grid for the editor
    tme->setup_grid();
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

    if (!tme) return;

    // Let the TileMapEditor handle its own input processing
    tme->process_editor_input();

}

void Engine::render_editor()
{
}

