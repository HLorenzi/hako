#include "basic.h"


Hako::Error Test::Basic::init()
{
	this->color_buffer.init();
	this->color_buffer.set_dimensions(640, 480);
	this->color_buffer.set_format(Hako::Gfx::FrameBufferFormat::RGBA8);
	this->color_buffer.generate();


	this->material.init();
#ifdef HAKO_MODULE_GFX_OPENGL
	auto vertex_src = "#version 330\n in vec3 in_position; uniform mat4 matrix_projview; uniform mat4 matrix_model; void main() { gl_Position = matrix_projview * matrix_model * vec4(in_position, 1); }";
	auto pixel_src = "#version 330\n out vec4 out_color; void main() { out_color = vec4(1, 0, 0, 1); }";
	this->material.set_shader_sources(vertex_src, pixel_src);
#endif
	this->material.generate();


	this->mesh.init(3, 3, Hako::Gfx::MeshData::Position);
	float mesh_positions[] = { 0, 0, 0,  100, 0, 0,  0, 100, 0 };
	unsigned int mesh_indices[] = { 0, 1, 2 };
	this->mesh.set_data(Hako::Gfx::MeshData::Position, 0, 3, mesh_positions);
	this->mesh.set_indices(0, 3, mesh_indices);
	this->mesh.generate();


	this->scene.init();
	this->node_renderer = Hako::Gfx::SceneNode::make_renderer();
	this->node_renderer.set_renderer_mesh(&mesh, &material);
	this->scene.add(this->node_renderer);


	this->camera.init();
	this->camera.set_projection_ortho(-640, 640, -480, 480, -100, 100);
	this->camera.set_lookat(
		Hako::Math::Vector3::make(0, 0, 0),
		Hako::Math::Vector3::make(0, 0, 100),
		Hako::Math::Vector3::make(0, -1, 0));


	this->renderop.init();
	this->renderop.set_scene(&this->camera, &this->scene, 0);
	this->renderop.set_color_buffer(0, &this->color_buffer);
	this->renderop.set_clear_color(Hako::Math::Color::make(0, 0, 1, 1));
	this->renderop.generate();


	this->renderop_ref = Hako::singleton()->gfx_manager.add_operation(&this->renderop);


	this->time = 0;


	return Hako::Error::ok();
}


void Test::Basic::process()
{
	this->time += 0.1f;

	float x = cosf(this->time) * 100;
	float y = -sinf(this->time) * 100;
	this->camera.set_lookat(
		Hako::Math::Vector3::make(x, y, 0),
		Hako::Math::Vector3::make(x, y, 100),
		Hako::Math::Vector3::make(0, -1, 0));
}


void Test::Basic::shutdown()
{
	Hako::singleton()->gfx_manager.remove_operation(this->renderop_ref);
}
