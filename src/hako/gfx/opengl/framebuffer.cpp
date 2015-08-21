#ifdef HAKO_MODULE_GFX_OPENGL


#include <hako/gfx/opengl/framebuffer.h>
#include <hako/util/debug.h>


Hako::Error Hako::OpenGL::FrameBuffer::internal_generate()
{
	glGenTextures(1, &this->gl_buffer);
	glBindTexture(GL_TEXTURE_2D, this->gl_buffer);

	switch (this->format)
	{
	case Hako::Gfx::FrameBufferFormat::RGBA8:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		break;
	case Hako::Gfx::FrameBufferFormat::RGB16F:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		break;
	case Hako::Gfx::FrameBufferFormat::RGBA16F:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		break;
	case Hako::Gfx::FrameBufferFormat::Depth:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->width, this->height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		break;
	default:
		HAKO_WARNING("unimplemented framebuffer format");
		return Hako::Error::make(Hako::ErrorClass::Unsupported);
	}

	if (HAKO_OPENGL_CHECKERROR())
		return Hako::Error::make(Hako::ErrorClass::Unknown);

	return Hako::Error::ok();
}


#endif
