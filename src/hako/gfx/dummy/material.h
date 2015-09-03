#ifndef HAKO_GFX_DUMMY_MATERIAL_H
#define HAKO_GFX_DUMMY_MATERIAL_H


#include <hako/bindings.h>
#include <hako/util/error.h>
#include <hako/util/debug.h>


namespace Hako
{
	namespace Dummy
	{
		namespace Gfx
		{
			class Material
			{
			public:
				Material();
				~Material();
				void init();

				Hako::Error apply();
				void        destroy();


			protected:
				virtual void internal_init()
					{ }

				virtual Hako::Error internal_apply()
					{ return Hako::Error::ok(); }

				virtual void internal_destroy()
					{ }

				virtual unsigned int get_float_slot_num()   { return 0; }
				virtual unsigned int get_float2_slot_num()  { return 0; }
				virtual unsigned int get_float3_slot_num()  { return 0; }
				virtual unsigned int get_float4_slot_num()  { return 0; }
				virtual unsigned int get_matrix_slot_num()  { return 0; }
				virtual unsigned int get_texture_slot_num() { return 0; }

				virtual int get_float_slot(const char* name)   { HAKO_UNUSED(name); return -1; }
				virtual int get_float2_slot(const char* name)  { HAKO_UNUSED(name); return -1; }
				virtual int get_float3_slot(const char* name)  { HAKO_UNUSED(name); return -1; }
				virtual int get_float4_slot(const char* name)  { HAKO_UNUSED(name); return -1; }
				virtual int get_matrix_slot(const char* name)  { HAKO_UNUSED(name); return -1; }
				virtual int get_texture_slot(const char* name) { HAKO_UNUSED(name); return -1; }


			#ifdef HAKO_BUILD_DEBUG
				bool initialized;
				bool generated;
			#endif
			};
		}
	}
}


#endif
