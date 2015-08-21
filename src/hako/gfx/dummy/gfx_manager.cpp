#include <hako/gfx/dummy/gfx_manager.h>


Hako::Error Hako::Dummy::GfxManager::init()
{
	this->operations.init();
	return this->internal_init();
}


Hako::Dummy::GfxManager::RenderOperationReference Hako::Dummy::GfxManager::add_operation(Hako::Gfx::RenderOperation* op)
{
	return this->operations.add(op);
}
