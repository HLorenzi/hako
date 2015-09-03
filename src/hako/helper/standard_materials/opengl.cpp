#ifdef HAKO_MODULE_GFX_OPENGL


#include <hako/helper/standard_materials.h>
#include <hako/bindings_def.h>


namespace
{
	void set_options(Hako::Gfx::Material* material, Hako::Helper::StandardMaterials::Options options)
	{
		if (options.use_depth_test)
		{
			GLenum func = GL_ALWAYS;
			switch (options.depth_test_func)
			{
				case Hako::Gfx::DepthTestFunc::Always:         func = GL_ALWAYS; break;
				case Hako::Gfx::DepthTestFunc::Less:           func = GL_LESS; break;
				case Hako::Gfx::DepthTestFunc::LessOrEqual:    func = GL_LEQUAL; break;
				case Hako::Gfx::DepthTestFunc::Equal:          func = GL_EQUAL; break;
				case Hako::Gfx::DepthTestFunc::Greater:        func = GL_GREATER; break;
				case Hako::Gfx::DepthTestFunc::GreaterOrEqual: func = GL_GEQUAL; break;
				default: HAKO_WARNING("unimplemented"); break;
			}
			material->set_depth_test(true, func);
		}
		else
			material->set_depth_test(false, GL_ALWAYS);


		if (options.use_blending)
		{
			GLenum src = GL_SRC_ALPHA;
			GLenum dest = GL_ONE_MINUS_SRC_ALPHA;
			switch (options.blending_func)
			{
				case Hako::Gfx::BlendFunc::Normal:
					src  = GL_SRC_ALPHA;
					dest = GL_ONE_MINUS_SRC_ALPHA;
					break;
				case Hako::Gfx::BlendFunc::Additive:
					src  = GL_SRC_ALPHA;
					dest = GL_ONE;
					break;
				default: HAKO_WARNING("unimplemented"); break;
			}
			material->set_blending(true, src, dest);
		}
		else
			material->set_blending(false, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		material->set_culling(options.culling_func);
	}
}


void Hako::Helper::StandardMaterials::make_basic_color(Hako::Gfx::Material* material, Hako::Helper::StandardMaterials::Options options)
{
	material->init();

	const char* vertex_src =
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

	const char* pixel_src =
		"#version 330                 \n"
		"out vec4 out_color;          \n"
		"varying vec4 varying_color;  \n"
		"void main() {                \n"
		"  out_color = varying_color; \n"
		"}";

	material->set_shader_sources(vertex_src, pixel_src);
	set_options(material, options);
	material->apply();
}


void Hako::Helper::StandardMaterials::make_basic_textured_color(Hako::Gfx::Material* material, Hako::Helper::StandardMaterials::Options options)
{
	material->init();

	const char* vertex_src =
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

	const char* pixel_src =
		"#version 330                                                                \n"
		"out vec4 out_color;                                                         \n"
		"uniform sampler2D uniform_texture;                                          \n"
		"varying vec4 varying_color;                                                 \n"
		"varying vec2 varying_texcoord;                                              \n"
		"void main() {                                                               \n"
		"  out_color = varying_color * texture2D(uniform_texture, varying_texcoord); \n"
		"}";

	material->set_shader_sources(vertex_src, pixel_src);
	material->uniform_textures.set_length(1);
	material->uniform_textures[0].name            = "main_texture";
	material->uniform_textures[0].gl_uniform_name = "uniform_texture";
	set_options(material, options);
	material->apply();
}


#endif
