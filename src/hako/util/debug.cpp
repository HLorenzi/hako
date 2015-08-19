#ifdef HAKO_BUILD_DEBUG


#include "debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>


void Hako::assert_handler(bool condition, const char* msg, const char* filename, int line)
{
	if (condition)
		return;

	// A breakpoint may be set here to debug the callstack, for example.
	printf(
		"==========================================================\n"
		"HAKO_ASSERT FAILED: %s\n"
		"%s : %d\n"
		"==========================================================\n\n",
		msg, filename, line);

	// Useful to trap the debugger.
	*((int*)0) = 1234;

	abort();
}


#endif
