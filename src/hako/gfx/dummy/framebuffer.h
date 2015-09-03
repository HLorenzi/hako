#ifndef HAKO_GFX_DUMMY_FRAMEBUFFER_H
#define HAKO_GFX_DUMMY_FRAMEBUFFER_H


#include <hako/gfx/framebuffer.h>
#include <hako/util/error.h>


namespace Hako
{
	namespace Dummy
	{
		namespace Gfx
		{
			class FrameBuffer
			{
			public:
				FrameBuffer();
				~FrameBuffer();

				void init            ();
				void set_dimensions  (unsigned int width, unsigned int height);
				void set_format      (Hako::Gfx::FrameBufferFormat format);

				unsigned int get_width  ();
				unsigned int get_height ();

				Hako::Error apply ();
				void        destroy  ();


			protected:
				virtual Hako::Error internal_apply()
					{ return Hako::Error::ok(); }

				virtual void internal_destroy()
					{ }


			#ifdef HAKO_BUILD_DEBUG
				bool initialized;
				bool generated;
			#endif
				unsigned int width, height;
				Hako::Gfx::FrameBufferFormat format;
			};
		}
	}
}


#endif
