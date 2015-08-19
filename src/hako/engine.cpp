#include <hako/engine.h>
#include <hako/util/allocator.h>
#include <hako/util/debug.h>
#include <stdlib.h>


Hako::Engine* Hako::Engine::g_engine = nullptr;


Hako::Engine* Hako::Engine::singleton()
{
	HAKO_ASSERT(Hako::Engine::g_engine != nullptr, "engine has not been initialized");
	return Hako::Engine::g_engine;
}


void Hako::Engine::init()
{
	HAKO_ASSERT(Hako::Engine::g_engine == nullptr, "engine has already been initialized");

	Hako::Engine::g_engine = this;
	this->memory_manager.init();
	this->loop_manager.init();
}


void Hako::Engine::loop(Hako::Callback<void> loop_callback)
{
	this->loop_manager.loop(loop_callback);
}
