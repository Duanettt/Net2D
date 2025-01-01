#include "Engine/Engine.h"


int main()
{
	Engine& engine = Engine::get_instance();
	
	engine.init();
	engine.setup_renders();

	while (engine.is_running())
	{
		engine.update();
		engine.run();
		engine.process_input();
	}
}