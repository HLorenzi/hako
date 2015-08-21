#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H


#include <hako/engine.h>
#include <hako/util/debug.h>
#include <hako/util/error.h>


namespace Test
{
	class Framework
	{
	public:
		virtual Hako::Error init() = 0;
		virtual void        process() = 0;
		virtual void        shutdown() = 0;
	};
}


#endif
