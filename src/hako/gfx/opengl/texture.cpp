#ifdef HAKO_MODULE_GFX_OPENGL


#include <hako/gfx/opengl/texture.h>
#include <hako/gfx/texture.h>


void Hako::OpenGL::Texture::internal_init()
{
	this->gl_texture = 0;
}


Hako::Error Hako::OpenGL::Texture::internal_apply()
{
	HAKO_ASSERT(this->kind == Hako::Gfx::TextureKind::TwoDimensions, "unimplemented");

	glGenTextures(1, &this->gl_texture);
	glBindTexture(GL_TEXTURE_2D, this->gl_texture);

	switch (this->filter)
	{
		case Hako::Gfx::TextureFilter::Nearest:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			break;
		case Hako::Gfx::TextureFilter::Linear:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			break;
		default:
			HAKO_WARNING("unimplemented");
			break;
	}

	switch (this->wrapping)
	{
		case Hako::Gfx::TextureWrapping::Repeat:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			break;
		case Hako::Gfx::TextureWrapping::Clamp:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			break;
		default:
			HAKO_WARNING("unimplemented");
			break;
	}

	switch (this->format)
	{
		case Hako::Gfx::TextureFormat::LinearRGBA8:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
				this->data.two_d.width, this->data.two_d.height,
				0, GL_RGBA, GL_UNSIGNED_BYTE, this->data.two_d.data[0]);
			break;
		default:
			HAKO_WARNING("unimplemented");
			break;
	}

	HAKO_OPENGL_CHECKERROR();
	return Hako::Error::ok();
}


void Hako::OpenGL::Texture::internal_destroy()
{
	glDeleteTextures(1, &this->gl_texture);
	this->gl_texture = 0;
	HAKO_OPENGL_CHECKERROR();
}


#endif
