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


		Hako::MemoryManager memory_manager;
		Hako::LoopManager   loop_manager;
		Hako::GfxManager    gfx_manager;
	};


	Engine*         singleton();
	Hako::Allocator singleton_allocator();
}


#endif
