#ifdef HAKO_MODULE_GFX_OPENGL


#include <hako/gfx/opengl/includes.h>
#include <hako/util/debug.h>
#include <stdio.h>


void Hako::OpenGL::check_error(const char* file, int line)
{
	GLenum err;
	do
	{
		err = glGetError();
		if (err != GL_NO_ERROR)
		{
			printf("GL error: 0x%08X\nFILE: %s, line %d\n\n", (int)err, file, line);
			HAKO_ERROR("opengl error");
		}
	} while (err != GL_NO_ERROR);
}


#endif

