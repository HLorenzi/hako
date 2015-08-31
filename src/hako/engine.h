#ifndef HAKO_ENGINE_H
#define HAKO_ENGINE_H


#include <hako/bindings_def.h>
#include <hako/util/callback.h>


namespace Hako
{
	class Engine
	{
	public:
		void init();
		void show();
		void loop(Hako::Callback<void> loop_callback);
		void shutdown();

		void set_use_interpolation(bool use);
		void set_frames_per_sec(unsigned int num);
		void set_updates_per_sec(unsigned int num);


		Hako::MemoryManager memory_manager;
		Hako::LoopManager   loop_manager;
		Hako::GfxManager    gfx_manager;

		bool         use_interpolation;
		unsigned int desired_frames_per_sec;
		unsigned int desired_updates_per_sec;
	};


	Engine*           singleton();
	Hako::Allocator   singleton_allocator();
	Hako::GfxManager* singleton_gfx();
}


#endif
