#include "basic.h"
#include <hako/helper/standard_materials.h>


Hako::Error Test::Basic::init()
{
	this->color_buffer.init();
	this->color_buffer.set_dimensions(640, 480);
	this->color_buffer.set_format(Hako::Gfx::FrameBufferFormat::RGBA8);
	this->color_buffer.generate();


	Hako::Helper::StandardMaterials::make_basic_color(&this->material);


	this->mesh.init(3, 3, Hako::Gfx::MeshData::Position | Hako::Gfx::MeshData::Color);
	float mesh_positions[]      = { -15, -15, 0,  15, 0, 0,    0, 15, 0 };
	float mesh_colors[]         = { 1, 0, 0, 1,   0, 1, 0, 1,  0, 0, 1, 1 };
	unsigned int mesh_indices[] = { 0,            1,           2 };
	this->mesh.set_data(Hako::Gfx::MeshData::Position, 0, 3, mesh_positions);
	this->mesh.set_data(Hako::Gfx::MeshData::Color,    0, 3, mesh_colors);
	this->mesh.set_indices(0, 3, mesh_indices);
	this->mesh.generate();


	this->scene.init();
	this->node_renderer = Hako::Gfx::SceneNode::make_renderer();
	this->node_renderer.set_renderer_mesh(&mesh, &material);
	this->scene.add(this->node_renderer);


	this->camera.init();
	this->camera.set_projection_perspective(Hako::Math::deg_to_rad(45), 960.0f / 544.0f, 1, 200);
	this->camera.set_lookat(
		Hako::Math::Vector3::make(0, 0, 0),
		Hako::Math::Vector3::make(0, 0, 100),
		Hako::Math::Vector3::make(0, -1, 0));


	this->renderop.init();
	this->renderop.set_scene(&this->camera, &this->scene, 0);
	this->renderop.set_color_buffer(0, &this->color_buffer);
	this->renderop.set_clear_color(Hako::Math::Color::make(0, 0, 0, 1));
	this->renderop.generate();


	this->renderop_ref = Hako::singleton()->gfx_manager.add_operation(&this->renderop);


	this->time = 0;


	return Hako::Error::ok();
}


void Test::Basic::process()
{
	this->time += 0.1f;

	float x = cosf(this->time) * (60 + 30 * cosf(this->time / 8.0f));
	float y = sinf(this->time) * (60 + 30 * cosf(this->time / 8.0f));
	this->camera.set_lookat(
		Hako::Math::Vector3::make(x, y, 20),
		Hako::Math::Vector3::make(0, 0, 0),
		Hako::Math::Vector3::make(0, 0, 1));
}


void Test::Basic::shutdown()
{
	Hako::singleton()->gfx_manager.remove_operation(this->renderop_ref);
}
