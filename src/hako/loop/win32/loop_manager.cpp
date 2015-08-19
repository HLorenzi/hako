#ifdef HAKO_MODULE_LOOP_WIN32


#include <hako/loop/win32/loop_manager.h>


void Hako::Win32::LoopManager::init()
{

}


void Hako::Win32::LoopManager::loop(Hako::Callback<void> loop_callback)
{
	while (true)
		loop_callback.call();
}


#endif
