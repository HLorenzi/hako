#ifndef HAKO_MODULE_GFX_OPENGL


#include <hako/helper/standard_materials.h>
#include <hako/bindings_def.h>
#include <hako/util/debug.h>


void Hako::Helper::StandardMaterials::make_basic_color(Hako::Gfx::Material* material, Hako::Helper::StandardMaterials::Options options)
{
	HAKO_UNUSED(options);
	material->init();
	material->generate();
}


void Hako::Helper::StandardMaterials::make_basic_textured_color(Hako::Gfx::Material* material, Hako::Helper::StandardMaterials::Options options)
{
	HAKO_UNUSED(options);
	material->init();
	material->generate();
}


#endif
