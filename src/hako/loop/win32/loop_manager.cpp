#ifdef HAKO_MODULE_OS_WIN32


#include <hako/loop/win32/loop_manager.h>
#include <hako/engine.h>


void Hako::Win32::LoopManager::init()
{

}


long long win32_get_timer_microseconds()
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	LARGE_INTEGER timer;
	QueryPerformanceCounter(&timer);

	long long microsec = timer.QuadPart;
	microsec *= 1000000;
	microsec /= freq.QuadPart;
	return microsec;
}


void Hako::Win32::LoopManager::loop(Hako::Callback<void> loop_callback)
{
	long long timer_update_remaining = 0;
	long long timer_update_last = win32_get_timer_microseconds();

	while (true)
	{
		//unsigned int frames_psec  = Hako::singleton()->desired_frames_per_sec;
		unsigned int updates_psec = Hako::singleton()->desired_updates_per_sec;
		bool         use_interp   = Hako::singleton()->use_interpolation;

		long long timer_begin = win32_get_timer_microseconds();

		float interpolation = (timer_begin - timer_update_last) / (1000000.0f / (float)updates_psec);
		if (interpolation < 0) interpolation = 0;
		if (interpolation > 1) interpolation = 1;
		if (!use_interp)       interpolation = 1;
		Hako::singleton()->gfx_manager.render(interpolation);

		Hako::singleton()->gfx_manager.process_events();
		if (Hako::singleton()->gfx_manager.did_user_quit())
			break;

		while (timer_update_remaining > 0)
		{
			timer_update_remaining -= 1000000 / updates_psec;
			Hako::singleton()->gfx_manager.advance_interpolation_frame();
			loop_callback.call();
			timer_update_last = win32_get_timer_microseconds();
		}

		long long timer_frame = win32_get_timer_microseconds();
		long long millisec_to_sleep = (1000 / 120) - ((timer_frame - timer_begin) / 1000);

		if (millisec_to_sleep > 0)
			Sleep(millisec_to_sleep);

		long long timer_end = win32_get_timer_microseconds();
		timer_update_remaining += (timer_end - timer_begin);
	}
}


#endif
