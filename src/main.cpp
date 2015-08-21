#include <hako/engine.h>
#include <stdio.h>


void loop();


int main()
{
	// Init the engine.
	Hako::Engine engine;
	engine.init();
	engine.show();


	// FrameBuffer API test.
	Hako::Gfx::FrameBuffer framebuf;
	framebuf.init();
	framebuf.set_dimensions(640, 480);
	framebuf.set_format(Hako::Gfx::FrameBufferFormat::RGBA8);
	framebuf.generate();


	// Scene API test.
	Hako::Gfx::Scene scene;
	scene.init();
	scene.add(Hako::Gfx::SceneNode::make_render());


	// Camera API test.
	Hako::Gfx::Camera camera;
	camera.init();
	camera.set_projection_ortho(0, 640, 0, 480, -100, 100);


	// RenderOperation API test.
	Hako::Gfx::RenderOperation renderop;
	renderop.init();
	renderop.set_scene(&camera, &scene, 0);
	renderop.set_color_buffer(0, &framebuf);
	renderop.generate();


	Hako::singleton()->gfx_manager.add_operation(&renderop);


	// Run a test loop.
	engine.loop(Hako::Callback<void>::make_static<loop>());


	return 0;
}


void loop()
{
	//printf("Hello, loopy world!\n");
}
