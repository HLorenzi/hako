#ifdef HAKO_MODULE_GFX_OPENGL


#include <hako/bindings_def.h>
#include <hako/util/debug.h>
#include <stdio.h>


Hako::Error Hako::OpenGL::RenderOperation::internal_generate()
{
	// Set up an OpenGL framebuffer.
	glGenFramebuffers(1, &this->gl_framebuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->gl_framebuffer);

	for (int i = 0; i < 4; i++)
	{
		if (this->color_buffers[i] != nullptr)
			glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, this->color_buffers[i]->gl_buffer, 0);
	}

	if (this->depth_buffer != nullptr)
		glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->depth_buffer->gl_buffer, 0);

	GLenum e = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if (e != GL_FRAMEBUFFER_COMPLETE)
	{
		HAKO_WARNING("opengl framebuffer creation error");
		return Hako::Error::unknown();
	}

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	if (HAKO_OPENGL_CHECKERROR())
	{
		HAKO_WARNING("opengl framebuffer creation error");
		return Hako::Error::unknown();
	}

	return Hako::Error::ok();
}


void Hako::OpenGL::RenderOperation::render(float interpolation)
{
	HAKO_UNUSED(interpolation);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	if (this->should_clear_color)
		glClearColor(this->clear_color.r, this->clear_color.g, this->clear_color.b, this->clear_color.a);

	if (this->should_clear_depth)
		glClearDepth(this->clear_depth);

	glClear(
		(this->should_clear_color ? GL_COLOR_BUFFER_BIT : 0) |
		(this->should_clear_depth ? GL_DEPTH_BUFFER_BIT : 0));

	this->scene->refresh_matrices(0);
	Hako::Math::Matrix4 camera_projview = this->camera->get_matrix_projview(0);

	for (unsigned int i = 0; i < this->scene->renderers.length(); i++)
	{
		Hako::Gfx::SceneRenderer& renderer = this->scene->renderers.get_by_index(i);

		if (renderer.active)
		{
			this->bind_mesh(&renderer, &camera_projview);
			this->draw_mesh(&renderer);
		}
	}
}


void Hako::OpenGL::RenderOperation::bind_mesh(Hako::Gfx::SceneRenderer* renderer, Hako::Math::Matrix4* camera_projview)
{
	Hako::OpenGL::Material* material          = renderer->material;
	Hako::Gfx::MaterialProperties* properties = renderer->properties;
	Hako::OpenGL::Mesh* mesh                  = renderer->mesh;

	glUseProgram(material->gl_shader_program);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->gl_index_buffer);

	glEnableVertexAttribArray(material->attrib_position);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->gl_data_buffers[Hako::Gfx::mesh_data_bit_to_index(Hako::Gfx::MeshData::Position)]);
	glVertexAttribPointer(material->attrib_position, Hako::Gfx::mesh_data_bit_to_elem_num(Hako::Gfx::MeshData::Position), GL_FLOAT, GL_FALSE, 0, (void*)0);

	if (material->attrib_color >= 0)
	{
		glEnableVertexAttribArray(material->attrib_color);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->gl_data_buffers[Hako::Gfx::mesh_data_bit_to_index(Hako::Gfx::MeshData::Color)]);
		glVertexAttribPointer(material->attrib_color, Hako::Gfx::mesh_data_bit_to_elem_num(Hako::Gfx::MeshData::Color), GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	if (material->attrib_texcoord >= 0)
	{
		glEnableVertexAttribArray(material->attrib_texcoord);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->gl_data_buffers[Hako::Gfx::mesh_data_bit_to_index(Hako::Gfx::MeshData::TexCoord)]);
		glVertexAttribPointer(material->attrib_texcoord, Hako::Gfx::mesh_data_bit_to_elem_num(Hako::Gfx::MeshData::TexCoord), GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	glUniformMatrix4fv(material->uniform_matrix_projview, 1, GL_FALSE, (GLfloat*)camera_projview->cell);
	glUniformMatrix4fv(material->uniform_matrix_model,    1, GL_FALSE, (GLfloat*)renderer->transform_matrix.cell);

	for (unsigned int i = 0; i < material->uniform_textures.length(); i++)
	{
		if (properties != nullptr && properties->slots_texture[i].used)
		{
			glUniform1i(material->uniform_textures[i].gl_location, 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, properties->slots_texture[i].data->gl_texture);
		}
	}

	material->set_render_state();
	HAKO_OPENGL_CHECKERROR();
}


void Hako::OpenGL::RenderOperation::draw_mesh(Hako::Gfx::SceneRenderer* renderer)
{
	Hako::OpenGL::Mesh* mesh = renderer->mesh;
	glDrawRangeElements(GL_TRIANGLES, 0, mesh->index_num, mesh->index_num, GL_UNSIGNED_INT, (void*)0);
	HAKO_OPENGL_CHECKERROR();
}


void Hako::OpenGL::RenderOperation::internal_destroy()
{
	glDeleteFramebuffers(1, &this->gl_framebuffer);
}

#endif
