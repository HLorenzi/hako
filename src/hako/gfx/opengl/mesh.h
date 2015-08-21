#ifdef HAKO_MODULE_GFX_OPENGL


#ifndef HAKO_GFX_OPENGL_MESH_H
#define HAKO_GFX_OPENGL_MESH_H


#include <hako/gfx/dummy/mesh.h>
#include <hako/gfx/opengl/includes.h>


namespace Hako
{
	namespace OpenGL
	{
		class Mesh : public Hako::Dummy::Gfx::Mesh
		{
		protected:
			void internal_init        () override;
			void internal_set_data    (int data_bit, unsigned int start, unsigned int count, float* data) override;
			void internal_set_indices (unsigned int start, unsigned int count, unsigned int* indices) override;


			GLuint gl_data_buffers[3];
			GLuint gl_index_buffer;
		};
	}
}


#endif


#endif
