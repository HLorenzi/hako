#ifdef HAKO_MODULE_GFX_OPENGL


#ifndef HAKO_GFX_OPENGL_FRAMEBUFFER_H
#define HAKO_GFX_OPENGL_FRAMEBUFFER_H


#include <hako/gfx/dummy/framebuffer.h>
#include <hako/gfx/opengl/includes.h>


namespace Hako
{
	namespace OpenGL
	{
		class RenderOperation;


		class FrameBuffer : public Hako::Dummy::Gfx::FrameBuffer
		{
			friend class Hako::OpenGL::RenderOperation;


		protected:
			Hako::Error internal_generate() override;
			void        internal_destroy() override;


			GLuint gl_buffer;
		};
	}
}


#endif


#endif
