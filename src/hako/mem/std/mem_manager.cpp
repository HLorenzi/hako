#ifdef HAKO_MODULE_MEM_STD


#include <hako/mem/std/mem_manager.h>
#include <hako/util/allocator.h>
#include <stdlib.h>


void Hako::Std::MemoryManager::init()
{

}


Hako::Allocator Hako::Std::MemoryManager::get_allocator()
{
	Hako::Allocator alloc_obj;

	alloc_obj.allocate   = Hako::Allocator::AllocateCallback::
		make_member<Hako::Std::MemoryManager, &Hako::Std::MemoryManager::mem_alloc>(this);

	alloc_obj.free       = Hako::Allocator::FreeCallback::
		make_member<Hako::Std::MemoryManager, &Hako::Std::MemoryManager::mem_free>(this);

	alloc_obj.reallocate = Hako::Allocator::ReallocateCallback::
		make_member<Hako::Std::MemoryManager, &Hako::Std::MemoryManager::mem_realloc>(this);

	return alloc_obj;
}


void* Hako::Std::MemoryManager::mem_alloc(unsigned int size, unsigned int align)
{
	HAKO_UNUSED(align);
	return malloc(size);
}


void Hako::Std::MemoryManager::mem_free(void* ptr)
{
	free(ptr);
}


bool Hako::Std::MemoryManager::mem_realloc(
	void** ptr,
	unsigned int old_size, unsigned int old_align,
	unsigned int new_size, unsigned int new_align)
{
	HAKO_UNUSED(old_size);
	HAKO_UNUSED(old_align);
	HAKO_UNUSED(new_align);
	*ptr = realloc(*ptr, new_size);
	return true;
}


#endif
