#include <hako/gfx/dummy/texture.h>
#include <hako/gfx/texture.h>


Hako::Dummy::Gfx::Texture::Texture()
{
#ifdef HAKO_BUILD_DEBUG
	this->initialized = false;
	this->generated   = false;
#endif
}


Hako::Dummy::Gfx::Texture::~Texture()
{
	HAKO_ASSERT(!this->generated, "possible resource leak; destroy() was not called");
}


void Hako::Dummy::Gfx::Texture::init()
{
	HAKO_ASSERT(!this->initialized, "init() has already been called");
	this->kind     = Hako::Gfx::TextureKind::TwoDimensions;
	this->format   = Hako::Gfx::TextureFormat::LinearRGBA8;
	this->filter   = Hako::Gfx::TextureFilter::Nearest;
	this->wrapping = Hako::Gfx::TextureWrapping::Repeat;
#ifdef HAKO_BUILD_DEBUG
	this->initialized = true;
#endif
}


void Hako::Dummy::Gfx::Texture::set_2d(unsigned int width, unsigned int height, unsigned int mip_levels)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(width > 0, "width must not be zero");
	HAKO_ASSERT(height > 0, "height must not be zero");
	HAKO_ASSERT(mip_levels > 0, "mip_levels must not be zero");
	this->kind                  = Hako::Gfx::TextureKind::TwoDimensions;
	this->data.two_d.width      = width;
	this->data.two_d.height     = height;
	this->data.two_d.mip_levels = mip_levels;
}


void Hako::Dummy::Gfx::Texture::set_filter(Hako::Gfx::TextureFilter filter)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	this->filter = filter;
}


void Hako::Dummy::Gfx::Texture::set_wrapping(Hako::Gfx::TextureWrapping wrapping)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	this->wrapping = wrapping;
}


void Hako::Dummy::Gfx::Texture::set_format(Hako::Gfx::TextureFormat format)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	this->format = format;
}


void Hako::Dummy::Gfx::Texture::set_data(unsigned int index, unsigned int mip_level, void* data)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	if (this->kind == Hako::Gfx::TextureKind::TwoDimensions)
	{
		HAKO_UNUSED(index);
		HAKO_ASSERT(index == 0, "index is unused in 2D textures and must be 0");
		HAKO_ASSERT(mip_level < this->data.two_d.mip_levels, "mip_level out of bounds");
		HAKO_ASSERT(data != nullptr, "data must not be null");
		this->data.two_d.data[mip_level] = data;
	}
}


Hako::Error Hako::Dummy::Gfx::Texture::apply()
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(!this->generated, "apply() has already been called");

	Hako::Error err = this->internal_apply();
#ifdef HAKO_BUILD_DEBUG
	if (err.is_ok())
		this->generated = true;
#endif

	return err;
}


void Hako::Dummy::Gfx::Texture::destroy()
{
	HAKO_ASSERT(this->initialized, "init() has not been called");
	HAKO_ASSERT(this->generated, "apply() has not been called");
	this->internal_destroy();
#ifdef HAKO_BUILD_DEBUG
	this->generated = false;
#endif
}
