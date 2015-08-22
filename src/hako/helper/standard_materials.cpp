#include <hako/helper/standard_materials.h>
#include <hako/bindings_def.h>


void Hako::Helper::StandardMaterials::Options::init()
{
	this->use_depth_test = false;
	this->use_blending   = false;
	this->culling_func   = Hako::Gfx::CullFunc::NoCull;
}


void Hako::Helper::StandardMaterials::Options::set_depth_test(Hako::Gfx::DepthTestFunc func)
{
	this->use_depth_test  = true;
	this->depth_test_func = func;
}


void Hako::Helper::StandardMaterials::Options::set_blending(Hako::Gfx::BlendFunc func)
{
	this->use_blending  = true;
	this->blending_func = func;
}


void Hako::Helper::StandardMaterials::Options::set_culling(Hako::Gfx::CullFunc func)
{
	this->culling_func = func;
}
