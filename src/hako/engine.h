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


		static Engine* g_engine;
		static Engine* singleton();

		void init();
		void loop(Hako::Callback<void> loop_callback);
	};
}


#endif
