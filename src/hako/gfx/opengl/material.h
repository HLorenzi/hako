#ifdef HAKO_MODULE_GFX_OPENGL


#ifndef HAKO_GFX_OPENGL_MATERIAL_H
#define HAKO_GFX_OPENGL_MATERIAL_H


#include <hako/gfx/dummy/material.h>
#include <hako/gfx/opengl/includes.h>
#include <hako/util/ds_vector.h>


namespace Hako
{
	namespace OpenGL
	{
		class RenderOperation;


		class Material : public Hako::Dummy::Gfx::Material
		{
			friend class Hako::OpenGL::RenderOperation;


		public:
			class Uniform
			{
			public:
				const char* name;
				const char* gl_uniform_name;
				GLint       gl_location;
			};


			void set_shader_sources(const char* vertex_src, const char* pixel_src);
			void set_depth_test(bool use, GLenum func);
			void set_blending(bool use, GLenum src, GLenum dest);
			void set_culling(Hako::Gfx::CullFunc func);
			void set_render_state();

			unsigned int get_texture_slot_num() override;
			int get_texture_slot(const char* name) override;


			Hako::DS::Vector<Uniform> uniform_textures;


		protected:
			void        internal_init() override;
			Hako::Error internal_apply() override;
			void        internal_destroy() override;


			void* vertex_shader_source;
			void* pixel_shader_source;

			GLuint gl_vertex_shader;
			GLuint gl_pixel_shader;
			GLuint gl_shader_program;

			GLint attrib_position;
			GLint attrib_color;
			GLint attrib_normal;
			GLint attrib_texcoord;

			GLint uniform_matrix_projview;
			GLint uniform_matrix_model;

			bool use_depth_test;
			GLenum depth_test_func;
			bool use_blending;
			GLenum blending_src, blending_dest;
			Hako::Gfx::CullFunc culling_func;
		};
	}
}


#endif


#endif
