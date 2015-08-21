#ifdef HAKO_MODULE_GFX_OPENGL


#ifndef HAKO_GFX_OPENGL_RENDEROP_H
#define HAKO_GFX_OPENGL_RENDEROP_H


#include <hako/gfx/dummy/renderop.h>
#include <hako/gfx/opengl/includes.h>


namespace Hako
{
	namespace OpenGL
	{
		class RenderOperation : public Hako::Dummy::Gfx::RenderOperation
		{
		public:
			void render(float interpolation);


		protected:
			Hako::Error internal_generate() override;

			void bind_mesh(Hako::Gfx::SceneNode* renderer);
			void draw_mesh(Hako::Gfx::SceneNode* renderer);


			GLuint gl_framebuffer;
		};
	}
}


#endif


#endif
