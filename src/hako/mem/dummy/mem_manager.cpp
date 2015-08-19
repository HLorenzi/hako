#include <hako/mem/dummy/mem_manager.h>
#include <hako/util/allocator.h>


Hako::Allocator Hako::Dummy::MemoryManager::get_allocator()
{
	Hako::Allocator alloc_obj;
	return alloc_obj;
}
