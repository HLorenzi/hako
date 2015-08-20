#ifdef HAKO_MODULE_OS_WIN32


#include <hako/loop/win32/loop_manager.h>
#include <hako/engine.h>


void Hako::Win32::LoopManager::init()
{

}


void Hako::Win32::LoopManager::loop(Hako::Callback<void> loop_callback)
{
	while (true)
	{
		Hako::singleton()->gfx_manager.process_events();
		if (Hako::singleton()->gfx_manager.did_user_quit())
			break;

		loop_callback.call();
	}
}


#endif
