#ifndef HAKO_GFX_DUMMY_GFXMANAGER_H
#define HAKO_GFX_DUMMY_GFXMANAGER_H


#include <hako/util/error.h>


namespace Hako
{
	namespace Dummy
	{
		class GfxManager
		{
		public:
			virtual Hako::Error init()
				{ return Hako::Error::ok(); }

			virtual Hako::Error show()
				{ return Hako::Error::ok(); }

			virtual Hako::Error shutdown()
				{ return Hako::Error::ok(); }
		};
	}
}


#endif
