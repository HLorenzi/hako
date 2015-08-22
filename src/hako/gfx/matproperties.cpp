#include <hako/gfx/matproperties.h>


Hako::Gfx::MaterialProperties::MaterialProperties()
{
#ifdef HAKO_BUILD_DEBUG
	this->initialized = false;
	this->bound       = false;
#endif
}


Hako::Gfx::MaterialProperties::~MaterialProperties()
{
	HAKO_ASSERT(!this->bound, "possible resource leak; destroy() was not called");
}


void Hako::Gfx::MaterialProperties::init()
{
	HAKO_ASSERT(!this->initialized, "init() has already been called");
	this->material = nullptr;
	this->slots_float   .init();
	this->slots_float2  .init();
	this->slots_float3  .init();
	this->slots_float4  .init();
	this->slots_matrix  .init();
	this->slots_texture .init();
#ifdef HAKO_BUILD_DEBUG
	this->initialized = false;
#endif
}


void Hako::Gfx::MaterialProperties::destroy()
{
	this->material = nullptr;
#ifdef HAKO_BUILD_DEBUG
	this->bound = false;
#endif
}


void Hako::Gfx::MaterialProperties::set_material(Hako::Gfx::Material* material)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	this->material = material;
#ifdef HAKO_BUILD_DEBUG
	this->bound = true;
#endif
}


void Hako::Gfx::MaterialProperties::set_float(unsigned int slot, float f)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(this->bound, "set_material() must be called before");
	HAKO_ASSERT(slot < this->slots_float.length(), "slot out of bounds");
	this->slots_float[slot].used = true;
	this->slots_float[slot].data = f;
}


void Hako::Gfx::MaterialProperties::set_float2(unsigned int slot, Hako::Math::Vector2 vec)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(this->bound, "set_material() must be called before");
	HAKO_ASSERT(slot < this->slots_float2.length(), "slot out of bounds");
	this->slots_float2[slot].used = true;
	this->slots_float2[slot].data = vec;
}


void Hako::Gfx::MaterialProperties::set_float3(unsigned int slot, Hako::Math::Vector3 vec)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(this->bound, "set_material() must be called before");
	HAKO_ASSERT(slot < this->slots_float3.length(), "slot out of bounds");
	this->slots_float3[slot].used = true;
	this->slots_float3[slot].data = vec;
}


void Hako::Gfx::MaterialProperties::set_float4(unsigned int slot, Hako::Math::Vector4 vec)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(this->bound, "set_material() must be called before");
	HAKO_ASSERT(slot < this->slots_float4.length(), "slot out of bounds");
	this->slots_float4[slot].used = true;
	this->slots_float4[slot].data = vec;
}


void Hako::Gfx::MaterialProperties::set_matrix(unsigned int slot, Hako::Math::Matrix4 matrix)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(this->bound, "set_material() must be called before");
	HAKO_ASSERT(slot < this->slots_matrix.length(), "slot out of bounds");
	this->slots_matrix[slot].used = true;
	this->slots_matrix[slot].data = matrix;
}


void Hako::Gfx::MaterialProperties::set_texture(unsigned int slot, Hako::Gfx::Texture* texture)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(this->bound, "set_material() must be called before");
	HAKO_ASSERT(slot < this->slots_texture.length(), "slot out of bounds");
	this->slots_texture[slot].used = true;
	this->slots_texture[slot].data = texture;
}


void Hako::Gfx::MaterialProperties::clear_float(unsigned int slot)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(this->bound, "set_material() must be called before");
	HAKO_ASSERT(slot < this->slots_float.length(), "slot out of bounds");
	this->slots_float[slot].used = false;
}


void Hako::Gfx::MaterialProperties::clear_float2(unsigned int slot)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(this->bound, "set_material() must be called before");
	HAKO_ASSERT(slot < this->slots_float2.length(), "slot out of bounds");
	this->slots_float2[slot].used = false;
}


void Hako::Gfx::MaterialProperties::clear_float3(unsigned int slot)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(this->bound, "set_material() must be called before");
	HAKO_ASSERT(slot < this->slots_float3.length(), "slot out of bounds");
	this->slots_float3[slot].used = false;
}


void Hako::Gfx::MaterialProperties::clear_float4(unsigned int slot)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(this->bound, "set_material() must be called before");
	HAKO_ASSERT(slot < this->slots_float4.length(), "slot out of bounds");
	this->slots_float4[slot].used = false;
}


void Hako::Gfx::MaterialProperties::clear_matrix(unsigned int slot)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(this->bound, "set_material() must be called before");
	HAKO_ASSERT(slot < this->slots_matrix.length(), "slot out of bounds");
	this->slots_matrix[slot].used = false;
}


void Hako::Gfx::MaterialProperties::clear_texture(unsigned int slot)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(this->bound, "set_material() must be called before");
	HAKO_ASSERT(slot < this->slots_texture.length(), "slot out of bounds");
	this->slots_texture[slot].used = false;
}
