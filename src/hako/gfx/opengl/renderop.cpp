#ifdef HAKO_MODULE_GFX_OPENGL


#include <hako/gfx/opengl/renderop.h>
#include <hako/util/debug.h>


Hako::Error Hako::OpenGL::RenderOperation::internal_generate()
{
	return Hako::Error::ok();
}


void Hako::OpenGL::RenderOperation::render(float interpolation)
{
	HAKO_UNUSED(interpolation);
}


#endif
