#ifndef HAKO_UTIL_DEBUG_H
#define HAKO_UTIL_DEBUG_H


#include <stdio.h>


// Suppresses unused parameter warnings.
#define HAKO_UNUSED(varname) \
	(void)varname


#ifdef HAKO_BUILD_DEBUG


	namespace Hako
	{
		void assert_handler(bool condition, const char* msg, const char* filename, int line);
		void warning_handler(bool condition, const char* msg, const char* filename, int line);
	}


	// Runtime assert.
	#define HAKO_ASSERT(cond, msg) \
		do { Hako::assert_handler(cond, msg, __FILE__, __LINE__); } while (0)


	// Runtime assert that does not crash the application.
	#define HAKO_CHECK(cond, msg) \
		do { Hako::warning_handler(cond, msg, __FILE__, __LINE__); } while (0)


	// Runtime error.
	#define HAKO_ERROR(msg) \
		HAKO_ASSERT(false, msg)


	// Runtime warning that is printed to the console, but does not crash the application.
	#define HAKO_WARNING(msg) \
		HAKO_CHECK(false, msg)


#else
	#define HAKO_ASSERT(cond, msg) do { } while (0)
	#define HAKO_CHECK(cond, msg)  do { } while (0)
	#define HAKO_ERROR(msg)        do { } while (0)
	#define HAKO_WARNING(msg)      do { } while (0)
#endif

#endif
