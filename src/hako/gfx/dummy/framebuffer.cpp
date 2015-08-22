#include <hako/gfx/dummy/framebuffer.h>
#include <hako/util/debug.h>


Hako::Dummy::Gfx::FrameBuffer::FrameBuffer()
{
#ifdef HAKO_BUILD_DEBUG
	this->initialized = false;
	this->generated   = false;
#endif
}


Hako::Dummy::Gfx::FrameBuffer::~FrameBuffer()
{
	HAKO_ASSERT(!this->generated, "possible resource leak; destroy() was not called");
}


void Hako::Dummy::Gfx::FrameBuffer::init()
{
	HAKO_ASSERT(!this->initialized, "init() has already been called");
#ifdef HAKO_BUILD_DEBUG
	this->initialized = true;
#endif
}


void Hako::Dummy::Gfx::FrameBuffer::set_dimensions(unsigned int width, unsigned int height)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(!this->generated, "cannot change framebuffer after it has been generated");
	this->width  = width;
	this->height = height;
}


void Hako::Dummy::Gfx::FrameBuffer::set_format(Hako::Gfx::FrameBufferFormat format)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(!this->generated, "cannot change framebuffer after it has been generated");
	this->format = format;
}


Hako::Error Hako::Dummy::Gfx::FrameBuffer::generate()
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


void Hako::Dummy::Gfx::FrameBuffer::destroy()
{
	HAKO_ASSERT(this->initialized, "init() has not been called");
	HAKO_ASSERT(this->generated, "generate() has not been called");
	this->internal_destroy();
#ifdef HAKO_BUILD_DEBUG
	this->generated = false;
#endif
}
