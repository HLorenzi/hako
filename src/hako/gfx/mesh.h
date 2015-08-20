#ifndef HAKO_GFX_MESH_H
#define HAKO_GFX_MESH_H


namespace Hako
{
	namespace Gfx
	{
		class MeshData
		{
		public:
			static const int Color  = (1 << 0);
			static const int Normal = (1 << 1);
			static const int UV     = (1 << 2);
		};
	}
}


#endif
