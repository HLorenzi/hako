#include <hako/engine.h>
#include <hako/gfx/scene.h>
#include <stdio.h>


void loop();


int main()
{
	// Init the engine.
	Hako::Engine engine;
	engine.init();
	engine.show();

	// Scene API test.
	Hako::Gfx::Scene scene;
	scene.init();
	scene.add(Hako::Gfx::SceneNode::make_render());

	// Run a test loop.
	engine.loop(Hako::Callback<void>::make_static<loop>());

	return 0;
}


void loop()
{
	printf("Hello, loopy world!\n");
}
