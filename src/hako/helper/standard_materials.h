#ifndef HAKO_HELPER_STANDARDMATERIALS_H
#define HAKO_HELPER_STANDARDMATERIALS_H


#include <hako/bindings.h>


namespace Hako
{
	namespace Helper
	{
		namespace StandardMaterials
		{
			class Options
			{
			public:
				void init();
				void set_depth_test(Hako::Gfx::DepthTestFunc func);
				void set_blending(Hako::Gfx::BlendFunc func);
				void set_culling(Hako::Gfx::CullFunc func);


				bool use_depth_test;
				Hako::Gfx::DepthTestFunc depth_test_func;
				bool use_blending;
				Hako::Gfx::BlendFunc blending_func;
				Hako::Gfx::CullFunc culling_func;
			};


			void make_basic_color          (Hako::Gfx::Material* material, Hako::Helper::StandardMaterials::Options options);
			void make_basic_textured_color (Hako::Gfx::Material* material, Hako::Helper::StandardMaterials::Options options);
		}
	}
}


#endif
