#ifdef HAKO_MODULE_GFX_OPENGL


#include <hako/gfx/opengl/material.h>
#include <hako/gfx/material.h>
#include <hako/util/debug.h>
#include <stdio.h>
#include <string.h>


namespace
{
	int compile_shader(void* data, GLuint type, GLuint* id)
	{
		*id = glCreateShader(type);
		glShaderSource(*id, 1, (char**)&data, nullptr);
		glCompileShader(*id);
		GLint compiled;
		glGetShaderiv(*id, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			GLint length;
			//glGetShaderiv(*id, GL_INFO_LOG_LENGTH, &length);
			char log[1024] = { 0 };
			glGetShaderInfoLog(*id, 1023, &length, log);
			printf("shader error:\n%s\n", log);
			HAKO_ERROR("could not compile opengl shader");
			return -1;
		}
		HAKO_OPENGL_CHECKERROR();
		return 0;
	}
}


void Hako::OpenGL::Material::internal_init()
{
	this->use_depth_test = false;
	this->use_blending   = false;
	this->culling_func   = Hako::Gfx::CullFunc::NoCull;
	this->uniform_textures.init();
}


void Hako::OpenGL::Material::set_shader_sources(const char* vertex_src, const char* pixel_src)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(vertex_src != nullptr, "vertex source must not be null");
	HAKO_ASSERT(pixel_src != nullptr, "pixel source must not be null");
	this->vertex_shader_source = static_cast<void*>(const_cast<char*>(vertex_src));
	this->pixel_shader_source  = static_cast<void*>(const_cast<char*>(pixel_src));
}


void Hako::OpenGL::Material::set_depth_test(bool use, GLenum func)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	this->use_depth_test  = use;
	this->depth_test_func = func;
}


void Hako::OpenGL::Material::set_blending(bool use, GLenum src, GLenum dest)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	this->use_blending  = use;
	this->blending_src  = src;
	this->blending_dest = dest;
}


void Hako::OpenGL::Material::set_culling(Hako::Gfx::CullFunc func)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	this->culling_func = func;
}


void Hako::OpenGL::Material::set_render_state()
{
	if (this->use_depth_test)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(this->depth_test_func);
	}
	else
		glDisable(GL_DEPTH_TEST);


	if (this->use_blending)
	{
		glEnable(GL_BLEND);
		glBlendFunc(this->blending_src, this->blending_dest);
	}
	else
		glDisable(GL_BLEND);


	if (this->culling_func != Hako::Gfx::CullFunc::NoCull)
	{
		glEnable(GL_CULL_FACE);
		switch (this->culling_func)
		{
			case Hako::Gfx::CullFunc::Clockwise:        glCullFace(GL_FRONT); break;
			case Hako::Gfx::CullFunc::CounterClockwise: glCullFace(GL_BACK); break;
			default: HAKO_WARNING("unimplemented"); break;
		}
	}
	else
		glDisable(GL_CULL_FACE);
}


Hako::Error Hako::OpenGL::Material::internal_generate()
{
	this->gl_shader_program = glCreateProgram();

	compile_shader(this->vertex_shader_source, GL_VERTEX_SHADER, &this->gl_vertex_shader);
	glAttachShader(this->gl_shader_program, this->gl_vertex_shader);

	compile_shader(this->pixel_shader_source, GL_FRAGMENT_SHADER, &this->gl_pixel_shader);
	glAttachShader(this->gl_shader_program, this->gl_pixel_shader);

	glBindFragDataLocation(this->gl_shader_program, 0, "out_color");

	glLinkProgram(this->gl_shader_program);
	glUseProgram(this->gl_shader_program);


	this->attrib_position = glGetAttribLocation(this->gl_shader_program, "in_position");
	this->attrib_color    = glGetAttribLocation(this->gl_shader_program, "in_color");
	this->attrib_normal   = glGetAttribLocation(this->gl_shader_program, "in_normal");
	this->attrib_texcoord = glGetAttribLocation(this->gl_shader_program, "in_texcoord");

	this->uniform_matrix_projview = glGetUniformLocation(this->gl_shader_program, "matrix_projview");
	this->uniform_matrix_model    = glGetUniformLocation(this->gl_shader_program, "matrix_model");

	for (unsigned int i = 0; i < this->uniform_textures.length(); i++)
	{
		this->uniform_textures[i].gl_location =
			glGetUniformLocation(this->gl_shader_program, this->uniform_textures[i].gl_uniform_name);

		HAKO_ASSERT(this->uniform_textures[i].gl_location >= 0, "could not bind a texture uniform");
	}

	HAKO_ASSERT(this->attrib_position >= 0,         "could not bind in_position attribute");
	HAKO_ASSERT(this->uniform_matrix_projview >= 0, "could not bind matrix_projview uniform");
	HAKO_ASSERT(this->uniform_matrix_model >= 0,    "could not bind matrix_model uniform");


	HAKO_OPENGL_CHECKERROR();
	return Hako::Error::ok();
}


void Hako::OpenGL::Material::internal_destroy()
{
	glDeleteShader(this->gl_vertex_shader);
	glDeleteShader(this->gl_pixel_shader);
	glDeleteProgram(this->gl_shader_program);
}


unsigned int Hako::OpenGL::Material::get_texture_slot_num()
{
	return this->uniform_textures.length();
}


int Hako::OpenGL::Material::get_texture_slot(const char* name)
{
	for (unsigned int i = 0; i < this->uniform_textures.length(); i++)
	{
		if (strcmp(name, this->uniform_textures[i].name) == 0)
			return i;
	}

	return -1;
}


#endif
