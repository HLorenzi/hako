#include <hako/gfx/dummy/gfx_manager.h>
#include <hako/bindings_def.h>


Hako::Error Hako::Dummy::GfxManager::init()
{
	this->operations.init();
	this->display_buffer = nullptr;
	return this->internal_init();
}


void Hako::Dummy::GfxManager::set_display_buffer(Hako::Gfx::FrameBuffer* buffer)
{
    this->internal_set_display_buffer(buffer);
    this->display_buffer = buffer;
}


void Hako::Dummy::GfxManager::add_operation(Hako::Gfx::RenderOperation* op)
{
    HAKO_ASSERT(this->operations.find_index(op) < 0, "operation given is already on the list");
	this->operations.add(op);
}


void Hako::Dummy::GfxManager::remove_operation(Hako::Gfx::RenderOperation* op)
{
    int op_index = this->operations.find_index(op);
    HAKO_ASSERT(op_index >= 0, "operation given is not on the list");
	this->operations.remove_by_index(op_index);
}


void Hako::Dummy::GfxManager::advance_interpolation_frame()
{
	for (unsigned int i = 0; i < this->operations.length(); i++)
		this->operations.get_by_index(i)->advance_interpolation_frame();
}
