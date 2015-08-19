#ifndef HAKO_MEM_DUMMY_MEMORYMANAGER_H
#define HAKO_MEM_DUMMY_MEMORYMANAGER_H


#include <hako/util/debug.h>


namespace Hako
{
	class Allocator;


	namespace Dummy
	{
		class MemoryManager
		{
		public:
			virtual void  init()
				{ }

			virtual Hako::Allocator get_allocator();

			virtual void* mem_alloc(unsigned int size, unsigned int align)
			{
				HAKO_UNUSED(size);
				HAKO_UNUSED(align);
				return nullptr;
			}

			virtual void  mem_free(void* ptr)
			{
				HAKO_UNUSED(ptr);
			}

			virtual bool  mem_realloc(void** ptr,
					unsigned int old_size, unsigned int old_align,
					unsigned int new_size, unsigned int new_align)
			{
				HAKO_UNUSED(ptr);
				HAKO_UNUSED(old_size);
				HAKO_UNUSED(old_align);
				HAKO_UNUSED(new_size);
				HAKO_UNUSED(new_align);
				return false;
			}
		};
	}
}


#endif
