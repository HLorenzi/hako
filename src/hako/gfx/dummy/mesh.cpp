#include <hako/gfx/dummy/mesh.h>
#include <hako/gfx/mesh.h>
#include <hako/util/debug.h>


Hako::Dummy::Gfx::Mesh::Mesh()
{
#ifdef HAKO_BUILD_DEBUG
	this->initialized = false;
	this->generated   = false;
#endif
}


Hako::Dummy::Gfx::Mesh::~Mesh()
{
	HAKO_ASSERT(!this->generated, "possible resource leak; destroy() was not called");
}


void Hako::Dummy::Gfx::Mesh::init(unsigned int vertex_num, unsigned int index_num, int data_bitfield)
{
	HAKO_ASSERT(!this->initialized, "init() has already been called");
	HAKO_ASSERT((data_bitfield & Hako::Gfx::MeshData::Invalid) == 0, "invalid data bitfield");

	this->vertex_num    = vertex_num;
	this->index_num     = index_num;
	this->data_bitfield = data_bitfield;

	this->internal_init();

#ifdef HAKO_BUILD_DEBUG
	this->initialized = true;
#endif
}


void Hako::Dummy::Gfx::Mesh::set_data(int data_bit, unsigned int start, unsigned int count, float* data)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(start + count <= this->vertex_num, "range out of bounds");
	HAKO_ASSERT((this->data_bitfield & data_bit) != 0, "mesh does not hold this kind of data");
	this->internal_set_data(data_bit, start, count, data);
}


void Hako::Dummy::Gfx::Mesh::set_indices(unsigned int start, unsigned int count, unsigned int* indices)
{
	HAKO_ASSERT(this->initialized, "init() must be called before");
	HAKO_ASSERT(start + count <= this->index_num, "range out of bounds");
	this->internal_set_indices(start, count, indices);
}


Hako::Error Hako::Dummy::Gfx::Mesh::apply()
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


void Hako::Dummy::Gfx::Mesh::destroy()
{
	HAKO_ASSERT(this->initialized, "init() has not been called");
	HAKO_ASSERT(this->generated, "apply() has not been called");
	this->internal_destroy();
#ifdef HAKO_BUILD_DEBUG
	this->generated = false;
#endif
}
