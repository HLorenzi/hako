#ifdef HAKO_MODULE_GFX_OPENGL


#include <hako/bindings_def.h>
#include <hako/util/debug.h>


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
		return Hako::Error::unknown();

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

	for (unsigned int i = 0; i < this->scene->tree.count(); i++)
	{
		Hako::Gfx::SceneNode& node = this->scene->tree.get_by_index(i);

		if (node.kind == Hako::Gfx::SceneNode::Kind::Renderer)
		{
			this->bind_mesh(&node);
			this->draw_mesh(&node);
		}
	}
}


void Hako::OpenGL::RenderOperation::bind_mesh(Hako::Gfx::SceneNode* renderer)
{
	Hako::OpenGL::Material* material = renderer->data.renderer.material;
	Hako::OpenGL::Mesh* mesh         = renderer->data.renderer.mesh;

	auto matrix_projview = this->camera->get_matrix_projview(0);
	auto matrix_model    = Hako::Math::Matrix4::make_identity();

	glUseProgram(material->gl_shader_program);

	glEnableVertexAttribArray(material->attrib_position);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->gl_data_buffers[Hako::Gfx::mesh_data_bit_to_index(Hako::Gfx::MeshData::Position)]);
	glVertexAttribPointer(material->attrib_position, Hako::Gfx::mesh_data_bit_to_elem_num(Hako::Gfx::MeshData::Position), GL_FLOAT, GL_FALSE, 0, (void*)0);

	glUniformMatrix4fv(material->uniform_matrix_projview, 1, GL_FALSE, (GLfloat*)matrix_projview.cell);
	glUniformMatrix4fv(material->uniform_matrix_model,    1, GL_FALSE, (GLfloat*)matrix_model.cell);
	HAKO_OPENGL_CHECKERROR();
}


void Hako::OpenGL::RenderOperation::draw_mesh(Hako::Gfx::SceneNode* renderer)
{
	Hako::OpenGL::Mesh* mesh = renderer->data.renderer.mesh;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->gl_index_buffer);
	glDrawRangeElements(GL_TRIANGLES, 0, mesh->index_num, mesh->index_num, GL_UNSIGNED_INT, (void*)0);
	HAKO_OPENGL_CHECKERROR();
}


#endif
