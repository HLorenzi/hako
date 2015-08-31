#ifndef HAKO_HELPER_DEBUG_FONT_H
#define HAKO_HELPER_DEBUG_FONT_H


#include <hako/bindings_def.h>


namespace Hako
{
	namespace Helper
	{
		class DebugFont
		{
		public:
			DebugFont();
			~DebugFont();

			void init(Hako::Gfx::RenderOperation* renderop, Hako::Gfx::FrameBuffer* color_buffer);
			void destroy();

			void set_text(const char* str);
			void set_position(float x, float y);



		public:
		#ifdef HAKO_BUILD_DEBUG
			bool initialized;
		#endif
			const char* str;
			float x, y;
			Hako::Gfx::Mesh               mesh;
			Hako::Gfx::Texture            texture;
			Hako::Gfx::Material           material;
			Hako::Gfx::MaterialProperties properties;
			Hako::Gfx::Camera             camera;
			Hako::Gfx::Scene              scene;
			Hako::Gfx::Scene::Reference   translate_node;
			Hako::Gfx::Scene::Reference   renderer_node;
			Hako::Gfx::FrameBuffer*       color_buffer;
			Hako::Gfx::RenderOperation    renderop;
		};
	}
}


#endif
