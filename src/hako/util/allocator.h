#ifndef HAKO_UTIL_ALLOCATOR_H
#define HAKO_UTIL_ALLOCATOR_H


#include <hako/util/callback.h>


namespace Hako
{
	class Allocator
	{
	public:
		typedef Hako::Callback<void*, unsigned int, unsigned int>
			AllocateCallback;

		typedef Hako::Callback<void, void*>
			FreeCallback;

		typedef Hako::Callback<bool, void**, unsigned int, unsigned int, unsigned int, unsigned int>
			ReallocateCallback;

		AllocateCallback    allocate;
		FreeCallback        free;
		ReallocateCallback  reallocate;
	};
}


#endif
