#ifdef HAKO_MODULE_OS_WIN32


#ifndef HAKO_LOOP_WIN32_LOOPMANAGER_H
#define HAKO_LOOP_WIN32_LOOPMANAGER_H


#include <hako/loop/dummy/loop_manager.h>


namespace Hako
{
	namespace Win32
	{
		class LoopManager : public Hako::Dummy::LoopManager
		{
		public:
			void init() override;
			void loop(Hako::Callback<void> loop_callback) override;
		};
	}
}


#endif


#endif
