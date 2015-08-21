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


			protected:
				virtual Hako::Error internal_generate()
					{ return Hako::Error::ok(); }


			#ifdef HAKO_BUILD_DEBUG
				bool initialized;
				bool generated;
			#endif
			};
		}
	}
}


#endif
