#include <hako/gfx/dummy/material.h>
#include <hako/util/debug.h>


Hako::Dummy::Gfx::Material::Material()
{
#ifdef HAKO_BUILD_DEBUG
	this->initialized = false;
	this->generated = false;
#endif
}


Hako::Dummy::Gfx::Material::~Material()
{
	HAKO_ASSERT(!this->generated, "possible resource leak; destroy() was not called");
}


void Hako::Dummy::Gfx::Material::init()
{
	HAKO_ASSERT(!this->initialized, "init() has already been called");
	this->internal_init();
#ifdef HAKO_BUILD_DEBUG
	this->initialized = true;
#endif
}


Hako::Error Hako::Dummy::Gfx::Material::generate()
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(!this->generated, "generate() has already been called");

	Hako::Error err = this->internal_generate();
#ifdef HAKO_BUILD_DEBUG
	if (err.is_ok())
		this->generated = true;
#endif

	return err;
}


void Hako::Dummy::Gfx::Material::destroy()
{
	HAKO_ASSERT(this->initialized, "init() has not been called");
	HAKO_ASSERT(this->generated, "generate() has not been called");
	this->internal_destroy();
#ifdef HAKO_BUILD_DEBUG
	this->generated = false;
#endif
}
