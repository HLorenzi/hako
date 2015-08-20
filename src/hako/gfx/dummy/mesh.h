#ifndef HAKO_GFX_DUMMY_MESH_H
#define HAKO_GFX_DUMMY_MESH_H


#include <hako/util/math_vector.h>
#include <hako/util/debug.h>


namespace Hako
{
	namespace Dummy
	{
		namespace Gfx
		{
			class Mesh
			{
			public:
				Mesh      ();
				~Mesh     ();
				void init (unsigned int vertex_num, unsigned int index_num, int data_bitfield);

				void set_data    (int data_bit, unsigned int start, unsigned int count, float* data);
				void set_indices (unsigned int start, unsigned int count, int* indices);


			protected:
				virtual void internal_init        ()
					{ }

				virtual void internal_set_data    (int data_bit, unsigned int start, unsigned int count, float* data)
				{
					HAKO_UNUSED(data_bit);
					HAKO_UNUSED(start);
					HAKO_UNUSED(count);
					HAKO_UNUSED(data);
				}

				virtual void internal_set_indices (unsigned int start, unsigned int count, int* indices)
				{
					HAKO_UNUSED(start);
					HAKO_UNUSED(count);
					HAKO_UNUSED(indices);
				}


			#ifdef HAKO_BUILD_DEBUG
				bool initialized;
			#endif
				int          data_bitfield;
				unsigned int vertex_num, index_num;
			};
		}
	}
}


#endif
