#ifndef HAKO_GFX_MATPROPERTIES_H
#define HAKO_GFX_MATPROPERTIES_H


#include <hako/bindings.h>
#include <hako/util/math_vector.h>
#include <hako/util/ds_vector.h>


namespace Hako
{
	namespace Gfx
	{
		class MaterialProperties
		{
			friend Hako::Gfx::RenderOperation;


		public:
			MaterialProperties();
			~MaterialProperties();
			void init();
			void destroy();

			void set_material(Hako::Gfx::Material* material);
			void set_float   (unsigned int slot, float f);
			void set_float2  (unsigned int slot, Hako::Math::Vector2 vec);
			void set_float3  (unsigned int slot, Hako::Math::Vector3 vec);
			void set_float4  (unsigned int slot, Hako::Math::Vector4 vec);
			void set_matrix  (unsigned int slot, Hako::Math::Matrix4 matrix);
			void set_texture (unsigned int slot, Hako::Gfx::Texture* texture);
			void clear_float   (unsigned int slot);
			void clear_float2  (unsigned int slot);
			void clear_float3  (unsigned int slot);
			void clear_float4  (unsigned int slot);
			void clear_matrix  (unsigned int slot);
			void clear_texture (unsigned int slot);


		protected:
			template <typename T>
			class Slot
			{
			public:
				bool used;
				T    data;
			};


		#ifdef HAKO_BUILD_DEBUG
			bool initialized;
			bool bound;
		#endif
			Hako::Gfx::Material*                        material;
			Hako::DS::Vector<Slot<float>>               slots_float;
			Hako::DS::Vector<Slot<Hako::Math::Vector2>> slots_float2;
			Hako::DS::Vector<Slot<Hako::Math::Vector3>> slots_float3;
			Hako::DS::Vector<Slot<Hako::Math::Vector4>> slots_float4;
			Hako::DS::Vector<Slot<Hako::Math::Matrix4>> slots_matrix;
			Hako::DS::Vector<Slot<Hako::Gfx::Texture*>> slots_texture;
		};
	}
}


#endif
