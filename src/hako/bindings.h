#ifndef HAKO_BINDINGS_H
#define HAKO_BINDINGS_H


namespace Hako
{
	class Engine;


	namespace Dummy
	{
		class MemoryManager;
		class LoopManager;
		class GfxManager;
	}


	namespace Std
	{
		class MemoryManager;
	}


	namespace Win32
	{
		class LoopManager;
		class GfxManager;
	}


	namespace OpenGL
	{

	}


	#ifdef HAKO_MODULE_MEM_STD
		typedef Hako::Std::MemoryManager MemoryManager;
	#else
		typedef Hako::Dummy::MemoryManager MemoryManager;
	#endif


	#ifdef HAKO_MODULE_OS_WIN32
		typedef Hako::Win32::LoopManager LoopManager;
	#else
		typedef Hako::Dummy::LoopManager LoopManager;
	#endif


	#ifdef HAKO_MODULE_OS_WIN32
		typedef Hako::Win32::GfxManager GfxManager;
	#else
		typedef Hako::Dummy::GfxManager GfxManager;
	#endif
}


#endif
