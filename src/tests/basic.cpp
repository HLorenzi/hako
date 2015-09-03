#include "basic.h"
#include <hako/helper/standard_materials.h>
#include <stdio.h>


Hako::Error Test::Basic::init()
{
	this->mesh.init(6, 6, Hako::Gfx::MeshData::Position | Hako::Gfx::MeshData::Color | Hako::Gfx::MeshData::TexCoord);
	float mesh_positions[]      = { -10, -15, 0,  10, -15, 0,  0, 15, 0,      -15, 0, 15,     15, 0, 15,      0, 0, -15 };
	float mesh_colors[]         = { 1, 0, 0, 1,   0, 1, 0, 1,  0, 0, 1, 1,    0.5f, 0, 0, 1,  0, 0.5f, 0, 1,  0, 0, 0.5f, 1 };
	float mesh_texcoords[]      = { 0, 0,         10, 0,       5, 10,         0, 0,           10, 0,          5, 10 };
	unsigned int mesh_indices[] = { 0,            1,           2,             3,              4,              5 };
	this->mesh.set_data(Hako::Gfx::MeshData::Position, 0, 6, mesh_positions);
	this->mesh.set_data(Hako::Gfx::MeshData::Color,    0, 6, mesh_colors);
	this->mesh.set_data(Hako::Gfx::MeshData::TexCoord, 0, 6, mesh_texcoords);
	this->mesh.set_indices(0, 6, mesh_indices);
	this->mesh.apply();


	Hako::Helper::StandardMaterials::Options options;
	options.init();
	options.set_depth_test(Hako::Gfx::DepthTestFunc::Less);
	options.set_blending(Hako::Gfx::BlendFunc::Additive);
	options.set_culling(Hako::Gfx::CullFunc::NoCull);
	Hako::Helper::StandardMaterials::make_basic_textured_color(&this->material, options);


	unsigned char texture_pixels[] = {
		255, 255, 255, 255,   128, 128, 128, 255,
		128, 128, 128, 255,   255, 255, 255, 255};
	this->texture.init();
	this->texture.set_2d(2, 2, 1);
	this->texture.set_format(Hako::Gfx::TextureFormat::LinearRGBA8);
	this->texture.set_data(0, 0, texture_pixels);
	this->texture.apply();


	this->properties.init();
	this->properties.set_material(&this->material);
	this->properties.set_texture(this->material.get_texture_slot("main_texture"), &this->texture);


	this->scene.init();

	this->node_rotation = this->scene.add_rotation(nullptr);
	this->scene.set_rotation(&this->node_rotation, Hako::Math::Vector3::make(0, 0, 1), 0);

	this->node_renderer = this->scene.add_renderer(&this->node_rotation);
	this->scene.set_renderer_mesh(&this->node_renderer, &this->mesh, &this->material, &this->properties);


	this->camera.init();
	this->camera.set_projection_perspective(Hako::Math::deg_to_rad(45), 256 / 256, 1, 200);
	this->camera.set_lookat(
		Hako::Math::Vector3::make(0, 0, 20),
		Hako::Math::Vector3::make(0, 0, 0),
		Hako::Math::Vector3::make(0, 0, 1));


	this->color_buffer.init();
	this->color_buffer.set_dimensions(256, 256);
	this->color_buffer.set_format(Hako::Gfx::FrameBufferFormat::RGBA8);
	this->color_buffer.apply();

	this->depth_buffer.init();
	this->depth_buffer.set_dimensions(256, 256);
	this->depth_buffer.set_format(Hako::Gfx::FrameBufferFormat::Depth);
	this->depth_buffer.apply();


	this->renderop.init();
	this->renderop.set_scene(&this->camera, &this->scene, 0);
	this->renderop.set_color_buffer(0, &this->color_buffer);
	this->renderop.set_depth_buffer(&this->depth_buffer);
	this->renderop.set_clear_color(Hako::Math::Color::make(0, 0, 0, 1));
	this->renderop.set_clear_depth(1);
	this->renderop.apply();


	Hako::singleton_gfx()->add_operation(&this->renderop);
	Hako::singleton_gfx()->set_display_buffer(&this->color_buffer);


	this->time = 0;


	Hako::singleton()->set_updates_per_sec(1);
	return Hako::Error::ok();
}


void Test::Basic::process()
{
	this->time += Hako::Math::pi * 2 / 6.0f;

	float x = (60 + 30 * cosf(this->time / 8.0f));
	float y = 0;
	this->camera.lerp_lookat(
		Hako::Math::Vector3::make(x, y, 20),
		Hako::Math::Vector3::make(0, 0, 0),
		Hako::Math::Vector3::make(0, 0, 1));

	this->scene.lerp_rotation(&this->node_rotation, Hako::Math::Vector3::make(0, 0, 1), this->time);
}


void Test::Basic::shutdown()
{
	Hako::singleton_gfx()->remove_operation(&this->renderop);
	this->renderop    .destroy();
	this->color_buffer.destroy();
	this->depth_buffer.destroy();
	this->properties  .destroy();
	this->material    .destroy();
	this->texture     .destroy();
	this->mesh        .destroy();
}
