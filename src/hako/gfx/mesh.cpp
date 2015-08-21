#include <hako/gfx/mesh.h>
#include <hako/util/debug.h>


int Hako::Gfx::mesh_data_bit_to_index(int data_bit)
{
	HAKO_ASSERT(data_bit != 0, "empty data bit");
	HAKO_ASSERT((data_bit & Hako::Gfx::MeshData::Invalid) == 0, "invalid data bit");

	int count = 0;
	while ((data_bit & 0x1) == 0)
	{
		data_bit >>= 1;
		count++;
	}

	return count;
}


int Hako::Gfx::mesh_data_bit_to_elem_num(int data_bit)
{
	HAKO_ASSERT(data_bit != 0, "empty data bit");
	HAKO_ASSERT((data_bit & Hako::Gfx::MeshData::Invalid) == 0, "invalid data bit");

	switch (data_bit)
	{
		case Hako::Gfx::MeshData::Position: return 3;
		case Hako::Gfx::MeshData::Color:    return 4;
		case Hako::Gfx::MeshData::Normal:   return 3;
		case Hako::Gfx::MeshData::TexCoord: return 2;
		default: break;
	}

	HAKO_ERROR("invalid data bit");
	return 1;
}
