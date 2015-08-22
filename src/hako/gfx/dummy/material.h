#ifndef HAKO_GFX_DUMMY_MATERIAL_H
#define HAKO_GFX_DUMMY_MATERIAL_H


#include <hako/bindings.h>
#include <hako/util/error.h>


namespace Hako
{
	namespace Dummy
	{
		namespace Gfx
		{
			class Material
			{
			public:
				Material();
				~Material();
				void init();

				Hako::Error generate();
				void        destroy();


			protected:
				virtual void internal_init()
					{ }

				virtual Hako::Error internal_generate()
					{ return Hako::Error::ok(); }

				virtual void internal_destroy()
					{ }


			#ifdef HAKO_BUILD_DEBUG
				bool initialized;
				bool generated;
			#endif
			};
		}
	}
}


#endif
