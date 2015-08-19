#ifndef HAKO_LOOP_DUMMY_LOOPMANAGER_H
#define HAKO_LOOP_DUMMY_LOOPMANAGER_H


#include <hako/util/callback.h>


namespace Hako
{
	namespace Dummy
	{
		class LoopManager
		{
		public:
			virtual void init()
				{ }

			virtual void loop(Hako::Callback<void> loop_callback)
			{
				HAKO_UNUSED(loop_callback);
			}
		};
	}
}


#endif
