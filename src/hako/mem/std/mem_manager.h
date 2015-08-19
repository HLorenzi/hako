#ifdef HAKO_MODULE_MEM_STD


#ifndef HAKO_MEM_STD_MEMORYMANAGER_H
#define HAKO_MEM_STD_MEMORYMANAGER_H


#include <hako/mem/dummy/mem_manager.h>


namespace Hako
{
	namespace Std
	{
		class MemoryManager : public Hako::Dummy::MemoryManager
		{
		public:
			void  init() override;

			Hako::Allocator get_allocator() override;

			void* mem_alloc  (unsigned int size, unsigned int align) override;
			void  mem_free   (void* ptr) override;
			bool  mem_realloc(void** ptr,
					unsigned int old_size, unsigned int old_align,
					unsigned int new_size, unsigned int new_align) override;
		};
	}
}


#endif


#endif
