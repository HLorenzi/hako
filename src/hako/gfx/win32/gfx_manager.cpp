#ifdef HAKO_MODULE_OS_WIN32


#ifdef HAKO_MODULE_GFX_OPENGL


#include <hako/gfx/win32/gfx_manager.h>
#include <hako/bindings_def.h>
#include <hako/gfx/opengl/includes.h>
#include <hako/util/debug.h>


Hako::Error Hako::Win32::GfxManager::internal_init()
{
	this->user_quit = false;
	return Hako::Error::ok();
}


Hako::Error Hako::Win32::GfxManager::show()
{
	//
	// Create a window descriptor.
	//
	HINSTANCE module_handle         = GetModuleHandle(NULL);

	WNDCLASSEX window_descriptor;
	window_descriptor.cbSize        = sizeof(WNDCLASSEX);
	window_descriptor.style         = CS_OWNDC;
	window_descriptor.lpfnWndProc   = window_callback;
	window_descriptor.cbClsExtra    = 0;
	window_descriptor.cbWndExtra    = 0;
	window_descriptor.hInstance     = module_handle;
	window_descriptor.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	window_descriptor.hCursor       = LoadCursor(NULL, IDC_ARROW);
	window_descriptor.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	window_descriptor.lpszMenuName  = NULL;
	window_descriptor.lpszClassName = "Hako Game Engine";
	window_descriptor.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&window_descriptor))
		HAKO_ERROR("unable to register Win32 window class");


	//
	// Instantiate and show window to user.
	//
	this->hwnd = CreateWindowEx(0,
		"Hako Game Engine", "Hako Game Engine",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		960, 544, NULL, NULL, module_handle, NULL);

	SetWindowLongPtr(this->hwnd, GWL_USERDATA, (LONG_PTR)this);
	ShowWindow(this->hwnd, true);

	this->opengl_enable(this->hwnd, &this->hdc, &this->hrc);
	Hako::OpenGL::win32_load_extensions();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
    SwapBuffers(this->hdc);

	this->set_window_size();
	glViewport(0, 0, this->window_width, this->window_height);

	return Hako::Error::ok();
}


Hako::Error Hako::Win32::GfxManager::shutdown()
{
	this->opengl_disable(this->hwnd, this->hdc, this->hrc);
	CloseWindow(this->hwnd);
	return Hako::Error::ok();
}


void Hako::Win32::GfxManager::set_window_size()
{
	RECT rect;
	GetClientRect(this->hwnd, &rect);
	this->window_width  = rect.right;
	this->window_height = rect.bottom;
}


void Hako::Win32::GfxManager::process_events()
{
	//
	// Process all queued Win32 event messages.
	//
	MSG window_message;
	while (PeekMessage(&window_message, NULL, 0, 0, PM_REMOVE))
	{
		if (window_message.message == WM_QUIT)
		{
			this->user_quit = true;
		}
		else
		{
			TranslateMessage(&window_message);
			DispatchMessage(&window_message);
		}
	}
}


bool Hako::Win32::GfxManager::did_user_quit()
{
	return this->user_quit;
}


LRESULT CALLBACK Hako::Win32::GfxManager::window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//
	// Switch on the message kind.
	//
	switch (uMsg)
	{
		case WM_CLOSE:
			PostQuitMessage(0);
			break;

		case WM_DESTROY:
			return 0;

		case WM_SIZE:
		{
			Hako::Win32::GfxManager* gfx_manager =
				(Hako::Win32::GfxManager*)GetWindowLongPtr(hwnd, GWL_USERDATA);
			gfx_manager->set_window_size();
			glViewport(0, 0, gfx_manager->window_width, gfx_manager->window_height);
			break;
		}

		case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			}
		}
			break;

		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}


void Hako::Win32::GfxManager::opengl_enable(HWND hwnd, HDC* hdc, HGLRC* hrc)
{
	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;

	*hdc = GetDC(hwnd);
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize      = sizeof(pfd);
	pfd.nVersion   = 1;
	pfd.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	iFormat = ChoosePixelFormat(*hdc, &pfd);
	SetPixelFormat(*hdc, iFormat, &pfd);

	*hrc = wglCreateContext(*hdc);
	wglMakeCurrent(*hdc, *hrc);
}


void Hako::Win32::GfxManager::opengl_disable(HWND hwnd, HDC hdc, HGLRC hrc)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hrc);
	ReleaseDC(hwnd, hdc);
}


void Hako::Win32::GfxManager::render()
{
	for (unsigned int i = 0; i < this->operations.length(); i++)
	{
		this->operations.get_by_index(i)->render(0);
	}
    SwapBuffers(this->hdc);
}


#endif


#endif
