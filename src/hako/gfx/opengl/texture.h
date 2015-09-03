#ifdef HAKO_MODULE_GFX_OPENGL


#ifndef HAKO_GFX_OPENGL_TEXTURE_H
#define HAKO_GFX_OPENGL_TEXTURE_H


#include <hako/bindings.h>
#include <hako/gfx/dummy/texture.h>
#include <hako/gfx/opengl/includes.h>


namespace Hako
{
	namespace OpenGL
	{
		class Texture : public Hako::Dummy::Gfx::Texture
		{
			friend Hako::Gfx::RenderOperation;


		protected:
			void        internal_init() override;
			Hako::Error internal_apply() override;
			void        internal_destroy() override;


			GLuint gl_texture;
		};
	}
}


#endif


#endif
