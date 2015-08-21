#include <hako/gfx/dummy/gfx_manager.h>


Hako::Error Hako::Dummy::GfxManager::init()
{
	this->scenes.init();
	return this->internal_init();
}


Hako::Dummy::GfxManager::SceneReference Hako::Dummy::GfxManager::add_scene(Hako::Gfx::Scene* scene)
{
	return this->scenes.add(scene);
}
