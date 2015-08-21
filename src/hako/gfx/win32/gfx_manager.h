#ifdef HAKO_MODULE_OS_WIN32


#ifdef HAKO_MODULE_GFX_OPENGL


#ifndef HAKO_GFX_WIN32_GFXMANAGER_H
#define HAKO_GFX_WIN32_GFXMANAGER_H


#include <hako/gfx/dummy/gfx_manager.h>
#include <windows.h>


namespace Hako
{
	namespace Win32
	{
		class GfxManager : public Hako::Dummy::GfxManager
		{
		public:
			Hako::Error internal_init() override;
			Hako::Error show() override;
			Hako::Error shutdown() override;

			void process_events();
			bool did_user_quit();
			void render();


		protected:
			// Win32 handle to the main window.
			HWND   hwnd;
			// Win32 handles to the render context.
			HDC    hdc;
			HGLRC  hrc;
			// Flag for whether the user closed the window.
			bool   user_quit;


			// Window callback function used by Win32.
			static LRESULT CALLBACK window_callback(
				HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

			// Win32 OpenGL setup.
			void opengl_enable  (HWND hwnd, HDC* hdc, HGLRC* hrc);
			void opengl_disable (HWND hwnd, HDC  hdc, HGLRC  hrc);
		};
	}
}


#endif


#endif


#endif
