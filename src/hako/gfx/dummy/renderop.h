#ifndef HAKO_GFX_DUMMY_RENDEROP_H
#define HAKO_GFX_DUMMY_RENDEROP_H


#include <hako/bindings.h>
#include <hako/util/error.h>


namespace Hako
{
	namespace Dummy
	{
		namespace Gfx
		{
			class RenderOperation
			{
			public:
				RenderOperation();
				~RenderOperation();
				void init();
				void set_scene(Hako::Gfx::Camera* camera, Hako::Gfx::Scene* scene, unsigned int mask);
				void set_color_buffer(unsigned int index, Hako::Gfx::FrameBuffer* colorbuf);
				void set_depth_buffer(Hako::Gfx::FrameBuffer* depthbuf);

				Hako::Error generate();


			protected:
				virtual Hako::Error internal_generate()
					{ return Hako::Error::ok(); }


			#ifdef HAKO_BUILD_DEBUG
				bool initialized;
				bool generated;
			#endif
				Hako::Gfx::Camera*      camera;
				unsigned int            camera_mask;
				Hako::Gfx::Scene*       scene;
				Hako::Gfx::FrameBuffer* color_buffers[4];
				Hako::Gfx::FrameBuffer* depth_buffer;
			};
		}
	}
}


#endif
