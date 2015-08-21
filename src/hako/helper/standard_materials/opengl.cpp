#ifdef HAKO_MODULE_GFX_OPENGL


#include <hako/helper/standard_materials.h>
#include <hako/bindings_def.h>


void Hako::Helper::StandardMaterials::make_basic_color(Hako::Gfx::Material* material)
{
	material->init();

	auto vertex_src =
		"#version 330                                                           \n"
		"in vec3 in_position;                                                   \n"
		"in vec4 in_color;                                                      \n"
		"uniform mat4 matrix_projview;                                          \n"
		"uniform mat4 matrix_model;                                             \n"
		"varying vec4 varying_color;                                            \n"
		"void main() {                                                          \n"
		"  gl_Position = matrix_projview * matrix_model * vec4(in_position, 1); \n"
		"  varying_color = in_color;                                            \n"
		"}";

	auto pixel_src =
		"#version 330                 \n"
		"out vec4 out_color;          \n"
		"varying vec4 varying_color;  \n"
		"void main() {                \n"
		"  out_color = varying_color; \n"
		"}";

	material->set_shader_sources(vertex_src, pixel_src);
	material->generate();
}


void Hako::Helper::StandardMaterials::make_basic_textured_color(Hako::Gfx::Material* material)
{
	// FIXME: Incomplete shader program.

	material->init();

	auto vertex_src =
		"#version 330                                                           \n"
		"in vec3 in_position;                                                   \n"
		"in vec4 in_color;                                                      \n"
		"in vec2 in_texcoord;                                                   \n"
		"uniform mat4 matrix_projview;                                          \n"
		"uniform mat4 matrix_model;                                             \n"
		"varying vec4 varying_color;                                            \n"
		"varying vec2 varying_texcoord;                                         \n"
		"void main() {                                                          \n"
		"  gl_Position = matrix_projview * matrix_model * vec4(in_position, 1); \n"
		"  varying_color = in_color;                                            \n"
		"  varying_texcoord = in_texcoord;                                      \n"
		"}";

	auto pixel_src =
		"#version 330                  \n"
		"out vec4 out_color;           \n"
		"varying vec4 varying_color;   \n"
		"varying vec2 varying_texcoord \n"
		"void main() {                 \n"
		"  out_color = varying_color;  \n"
		"}";

	material->set_shader_sources(vertex_src, pixel_src);
	material->generate();
}


#endif
