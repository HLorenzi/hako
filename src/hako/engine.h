#ifndef HAKO_ENGINE_H
#define HAKO_ENGINE_H


#include <hako/bindings_def.h>
#include <hako/util/callback.h>


namespace Hako
{
	class Engine
	{
	public:
		Hako::MemoryManager memory_manager;
		Hako::LoopManager   loop_manager;


		void init();
		void loop(Hako::Callback<void> loop_callback);
	};


	Engine*         singleton();
	Hako::Allocator singleton_allocator();
}


#endif
