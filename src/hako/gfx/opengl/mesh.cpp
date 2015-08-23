#ifdef HAKO_MODULE_GFX_OPENGL


#include <hako/gfx/opengl/mesh.h>
#include <hako/gfx/mesh.h>


void Hako::OpenGL::Mesh::internal_init()
{
	HAKO_ASSERT((data_bitfield & (~0xf)) == 0, "some data fields not implemented");

	for (int i = 0; i < DATA_BUFFER_NUM; i++)
	{
		int bit = (1 << i);
		if ((this->data_bitfield & bit) != 0)
			glGenBuffers(1, &this->gl_data_buffers[i]);
		else
			this->gl_data_buffers[i] = -1;
	}
	glGenBuffers(1, &this->gl_index_buffer);

	HAKO_OPENGL_CHECKERROR();
}


void Hako::OpenGL::Mesh::internal_set_data(int data_bit, unsigned int start, unsigned int count, float* data)
{
	HAKO_ASSERT(start == 0 && count == this->vertex_num, "unimplemented");
	HAKO_UNUSED(start);

	int byte_length = count * Hako::Gfx::mesh_data_bit_to_elem_num(data_bit) * sizeof(float);

	glBindBuffer(GL_ARRAY_BUFFER, this->gl_data_buffers[Hako::Gfx::mesh_data_bit_to_index(data_bit)]);
	glBufferData(GL_ARRAY_BUFFER, byte_length, data, GL_STATIC_DRAW);
	HAKO_OPENGL_CHECKERROR();
}


void Hako::OpenGL::Mesh::internal_set_indices(unsigned int start, unsigned int count, unsigned int* indices)
{
	HAKO_ASSERT(start == 0 && count == this->index_num, "unimplemented");
	HAKO_UNUSED(start);

	int byte_length = count * sizeof(unsigned int);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->gl_index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, byte_length, indices, GL_STATIC_DRAW);
	HAKO_OPENGL_CHECKERROR();
}


void Hako::OpenGL::Mesh::internal_destroy()
{
	for (int i = 0; i < DATA_BUFFER_NUM; i++)
	{
		int bit = (1 << i);
		if ((this->data_bitfield & bit) != 0)
			glDeleteBuffers(1, &this->gl_data_buffers[i]);
	}
	glDeleteBuffers(1, &this->gl_index_buffer);
	HAKO_OPENGL_CHECKERROR();
}


#endif
