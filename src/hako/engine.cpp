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


Hako::GfxManager* Hako::singleton_gfx()
{
	return &Hako::singleton()->gfx_manager;
}


void Hako::Engine::init()
{
	HAKO_ASSERT(singleton_engine == nullptr, "engine has already been initialized");

	singleton_engine = this;

	this->use_interpolation       = true;
	this->desired_frames_per_sec  = 60;
	this->desired_updates_per_sec = 60;

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


void Hako::Engine::set_use_interpolation(bool use)
{
	HAKO_ASSERT(singleton_engine != nullptr, "engine has not been initialized");
	this->use_interpolation = use;
}


void Hako::Engine::set_frames_per_sec(unsigned int num)
{
	HAKO_ASSERT(singleton_engine != nullptr, "engine has not been initialized");
	HAKO_ASSERT(num > 0, "frames per second must not be zero");
	HAKO_ASSERT(num <= 1024, "frames per second too high");
	this->desired_frames_per_sec = num;
}


void Hako::Engine::set_updates_per_sec(unsigned int num)
{
	HAKO_ASSERT(singleton_engine != nullptr, "engine has not been initialized");
	HAKO_ASSERT(num > 0, "updates per second must not be zero");
	HAKO_ASSERT(num <= 1024, "updates per second too high");
	this->desired_updates_per_sec = num;
}

