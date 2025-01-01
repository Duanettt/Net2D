#pragma once
#include "../Core/Window.h"
#include "Renderer.h"



class Engine
{
public:
	// Prevent other creation of engine instances.
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
	std::unique_ptr<Window> window;
	// Figure out another way to encorporate our cursor since I'm not too fond of it.
	Cursor* cursor;
	Renderer r;

	Engine() : window(nullptr), cursor(nullptr)
	{
	}

	~Engine()
	{
		delete(cursor);
	}
};

