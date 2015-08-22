#ifdef HAKO_MODULE_GFX_OPENGL


#include <hako/gfx/opengl/includes.h>
#include <hako/util/debug.h>
#include <stdio.h>


bool Hako::OpenGL::check_error(const char* file, int line)
{
	bool had_errors = false;
	GLenum err;
	do
	{
		err = glGetError();
		if (err != GL_NO_ERROR)
		{
			had_errors = true;
			printf("GL error: 0x%08X\nFILE: %s, line %d\n\n", (int)err, file, line);
			HAKO_ERROR("opengl error");
		}
	} while (err != GL_NO_ERROR);

	return had_errors;
}


#endif

