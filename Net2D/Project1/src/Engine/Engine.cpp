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
    window->SetCallbacks();
    window->SetWindowUserPointer(cursor);
    // set mouse call back soon
    //window.SetCallbacks();

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
    window->SetCallbacks();
    window->SetWindowUserPointer(cursor);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

void Engine::setup_renders()
{
    r.setup_shaders();
    r.setup_renderer();
}
void Engine::run()
{
    r.draw();


    glfwSwapBuffers(window->GetWindow());
    glfwPollEvents();
}


void Engine::process_input() {
    if (glfwGetKey(window->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window->GetWindow(), true);

    // Add your input processing code here
}

bool Engine::is_running() const {
    return !glfwWindowShouldClose(window->GetWindow());
}

