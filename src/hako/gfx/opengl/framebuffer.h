#ifdef HAKO_MODULE_GFX_OPENGL


#ifndef HAKO_GFX_OPENGL_FRAMEBUFFER_H
#define HAKO_GFX_OPENGL_FRAMEBUFFER_H


#include <hako/gfx/dummy/framebuffer.h>
#include <hako/gfx/opengl/includes.h>


namespace Hako
{
	namespace OpenGL
	{
		class FrameBuffer : public Hako::Dummy::Gfx::FrameBuffer
		{
		protected:
			Hako::Error internal_generate() override;


			GLuint gl_buffer;
		};
	}
}


#endif


#endif
