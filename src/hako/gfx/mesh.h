#ifndef HAKO_GFX_MESH_H
#define HAKO_GFX_MESH_H


namespace Hako
{
	namespace Gfx
	{
		class MeshData
		{
		public:
			static const int Position = (1 << 0);
			static const int Color    = (1 << 1);
			static const int Normal   = (1 << 2);
			static const int TexCoord = (1 << 3);

			static const int Last     = (TexCoord << 1);
			static const int Valid    = (Position | Color | Normal | TexCoord);
			static const int Invalid  = ~Valid;
		};


		int mesh_data_bit_to_index(int data_bit);
		int mesh_data_bit_to_elem_num(int data_bit);
	}
}


#endif
