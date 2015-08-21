#ifdef HAKO_MODULE_GFX_OPENGL


#ifndef HAKO_GFX_OPENGL_MATERIAL_H
#define HAKO_GFX_OPENGL_MATERIAL_H


#include <hako/gfx/dummy/material.h>
#include <hako/gfx/opengl/includes.h>


namespace Hako
{
	namespace OpenGL
	{
		class RenderOperation;


		class Material : public Hako::Dummy::Gfx::Material
		{
			friend class Hako::OpenGL::RenderOperation;


		public:
			void set_shader_sources(const char* vertex_src, const char* pixel_src);


		protected:
			Hako::Error internal_generate() override;


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
		};
	}
}


#endif


#endif
