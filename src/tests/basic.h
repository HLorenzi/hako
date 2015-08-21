#ifndef TEST_BASIC_H
#define TEST_BASIC_H


#include "framework.h"


namespace Test
{
	class Basic : public Framework
	{
	public:
		Hako::Error init() override;
		void        process() override;
		void        shutdown() override;


	protected:
		float time;

		Hako::Gfx::Mesh        mesh;
		Hako::Gfx::Material    material;

		Hako::Gfx::Scene       scene;
		Hako::Gfx::SceneNode   node_renderer;

		Hako::Gfx::Camera      camera;
		Hako::Gfx::FrameBuffer color_buffer;
		Hako::Gfx::FrameBuffer depth_buffer;

		Hako::Gfx::RenderOperation                 renderop;
		Hako::GfxManager::RenderOperationReference renderop_ref;
	};
}


#endif
