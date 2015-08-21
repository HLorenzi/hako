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


	// Material API test.
	Hako::Gfx::Material material;
	material.init();
#ifdef HAKO_MODULE_GFX_OPENGL
	auto vertex_src = "#version 330\n in vec3 in_position; uniform mat4 matrix_projview; uniform mat4 matrix_model; void main() { gl_Position = matrix_projview * matrix_model * vec4(in_position, 1); }";
	auto pixel_src = "#version 330\n out vec4 out_color; void main() { out_color = vec4(1, 0, 0, 1); }";
	material.set_shader_sources(vertex_src, pixel_src);
#endif
	material.generate();


	// Mesh API test.
	Hako::Gfx::Mesh mesh;
	mesh.init(3, 3, Hako::Gfx::MeshData::Position);
	float mesh_positions[] = { 0, 0, 0,  1, 0, 0,  0, 1, 0 };
	unsigned int mesh_indices[] = { 0, 1, 2 };
	mesh.set_data(Hako::Gfx::MeshData::Position, 0, 3, mesh_positions);
	mesh.set_indices(0, 3, mesh_indices);


	// Scene API test.
	Hako::Gfx::Scene scene;
	scene.init();
	auto renderer = Hako::Gfx::SceneNode::make_renderer();
	renderer.set_renderer_mesh(&mesh, &material);
	scene.add(renderer);


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
	Hako::singleton()->gfx_manager.render();


	// Run a test loop.
	engine.loop(Hako::Callback<void>::make_static<loop>());


	return 0;
}


void loop()
{
	//printf("Hello, loopy world!\n");
}
