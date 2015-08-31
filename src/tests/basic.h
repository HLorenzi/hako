#ifndef TEST_BASIC_H
#define TEST_BASIC_H


#include "framework.h"
#include <hako/helper/debug_font.h>


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

		Hako::Gfx::Mesh               mesh;
		Hako::Gfx::Texture            texture;
		Hako::Gfx::Material           material;
		Hako::Gfx::MaterialProperties properties;

		Hako::Gfx::Scene            scene;
		Hako::Gfx::Scene::Reference node_rotation;
		Hako::Gfx::Scene::Reference node_renderer;

		Hako::Gfx::Camera      camera;
		Hako::Gfx::FrameBuffer color_buffer;
		Hako::Gfx::FrameBuffer depth_buffer;

		Hako::Gfx::RenderOperation renderop;
	};
}


#endif
