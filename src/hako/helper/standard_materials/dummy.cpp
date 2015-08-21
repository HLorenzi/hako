#ifndef HAKO_MODULE_GFX_OPENGL


#include <hako/helper/standard_materials.h>
#include <hako/bindings_def.h>


void Hako::Helper::StandardMaterials::make_basic_color(Hako::Gfx::Material* material)
{
	material->init();
	material->generate();
}


void Hako::Helper::StandardMaterials::make_basic_textured_color(Hako::Gfx::Material* material)
{
	material->init();
	material->generate();
}


#endif
