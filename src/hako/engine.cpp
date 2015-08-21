#include <hako/engine.h>
#include <hako/util/allocator.h>
#include <hako/util/debug.h>
#include <stdlib.h>


Hako::Engine* singleton_engine = nullptr;


Hako::Engine* Hako::singleton()
{
	HAKO_ASSERT(singleton_engine != nullptr, "engine has not been initialized");
	return singleton_engine;
}


Hako::Allocator Hako::singleton_allocator()
{
	return Hako::singleton()->memory_manager.get_allocator();
}


void Hako::Engine::init()
{
	HAKO_ASSERT(singleton_engine == nullptr, "engine has already been initialized");

	singleton_engine = this;
	this->memory_manager.init();
	this->loop_manager.init();
	this->gfx_manager.init();
}


void Hako::Engine::show()
{
	HAKO_ASSERT(singleton_engine != nullptr, "engine has not been initialized");
	this->gfx_manager.show();
}


void Hako::Engine::loop(Hako::Callback<void> loop_callback)
{
	HAKO_ASSERT(singleton_engine != nullptr, "engine has not been initialized");
	this->loop_manager.loop(loop_callback);
}


void Hako::Engine::shutdown()
{
	HAKO_ASSERT(singleton_engine != nullptr, "engine has not been initialized");
	this->gfx_manager.shutdown();
}
