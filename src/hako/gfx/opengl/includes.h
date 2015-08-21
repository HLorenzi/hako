#ifdef HAKO_MODULE_GFX_OPENGL


#ifndef HAKO_GFX_OPENGL_INCLUDES_H
#define HAKO_GFX_OPENGL_INCLUDES_H


#ifdef HAKO_MODULE_OS_WIN32
	#include <windows.h>
	#include <gl/gl.h>
	#include "extensions_win32.h"
#endif

#ifdef HAKO_MODULE_OS_LINUX
	#include <GL/glx.h>
	#include <GL/gl.h>
	#include <X11/X.h>
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include "extensions_linux.h"
#endif


namespace Hako
{
	namespace OpenGL
	{
		bool check_error(const char* file, int line);
	}
}


#define HAKO_OPENGL_CHECKERROR() Hako::OpenGL::check_error(__FILE__, __LINE__)


#endif


#endif
