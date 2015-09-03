#ifndef HAKO_GFX_DUMMY_TEXTURE_H
#define HAKO_GFX_DUMMY_TEXTURE_H


#include <hako/bindings.h>
#include <hako/util/math_vector.h>
#include <hako/util/debug.h>
#include <hako/util/error.h>


namespace Hako
{
	namespace Dummy
	{
		namespace Gfx
		{
			class Texture
			{
			public:
				Texture();
				~Texture();
				void init();

				void set_2d       (unsigned int width, unsigned int height, unsigned int mip_levels);
				void set_filter   (Hako::Gfx::TextureFilter filter);
				void set_wrapping (Hako::Gfx::TextureWrapping wrapping);
				void set_format   (Hako::Gfx::TextureFormat format);
				void set_data     (unsigned int index, unsigned int mip_level, void* data);

				Hako::Error apply();
				void        destroy();


			protected:
				virtual void internal_init()
					{ }

				virtual Hako::Error internal_apply()
					{ return Hako::Error::ok(); }

				virtual void internal_destroy()
					{ }


			#ifdef HAKO_BUILD_DEBUG
				bool initialized;
				bool generated;
			#endif
				Hako::Gfx::TextureKind     kind;
				Hako::Gfx::TextureFormat   format;
				Hako::Gfx::TextureFilter   filter;
				Hako::Gfx::TextureWrapping wrapping;

				union
				{
					struct
					{
						unsigned int width, height;
						unsigned int mip_levels;
						void*        data[16];
					} two_d;
				} data;
			};
		}
	}
}


#endif
