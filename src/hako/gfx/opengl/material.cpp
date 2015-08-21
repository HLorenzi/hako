#ifdef HAKO_MODULE_GFX_OPENGL


#include <hako/gfx/opengl/material.h>
#include <hako/util/debug.h>
#include <stdio.h>


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


void Hako::OpenGL::Material::set_shader_sources(const char* vertex_src, const char* pixel_src)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(vertex_src != nullptr, "vertex source must not be null");
	HAKO_ASSERT(pixel_src != nullptr, "pixel source must not be null");
	this->vertex_shader_source = static_cast<void*>(const_cast<char*>(vertex_src));
	this->pixel_shader_source  = static_cast<void*>(const_cast<char*>(pixel_src));
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

	HAKO_ASSERT(this->attrib_position >= 0,         "could not bind in_position attribute");
	HAKO_ASSERT(this->uniform_matrix_projview >= 0, "could not bind matrix_projview uniform");
	HAKO_ASSERT(this->uniform_matrix_model >= 0,    "could not bind matrix_model uniform");


	HAKO_OPENGL_CHECKERROR();
	return Hako::Error::ok();
}


#endif
