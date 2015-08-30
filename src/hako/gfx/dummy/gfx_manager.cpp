#include <hako/gfx/dummy/gfx_manager.h>
#include <hako/bindings_def.h>


Hako::Error Hako::Dummy::GfxManager::init()
{
	this->operations.init();
	return this->internal_init();
}


Hako::Dummy::GfxManager::RenderOperationReference Hako::Dummy::GfxManager::add_operation(Hako::Gfx::RenderOperation* op)
{
	return this->operations.add(op);
}


void Hako::Dummy::GfxManager::remove_operation(RenderOperationReference& ref)
{
	this->operations.remove(ref);
}


void Hako::Dummy::GfxManager::advance_interpolation_frame()
{
	for (unsigned int i = 0; i < this->operations.length(); i++)
		this->operations.get_by_index(i)->advance_interpolation_frame();
}
