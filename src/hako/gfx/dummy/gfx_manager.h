#ifndef HAKO_GFX_DUMMY_GFXMANAGER_H
#define HAKO_GFX_DUMMY_GFXMANAGER_H


#include <hako/bindings.h>
#include <hako/util/error.h>
#include <hako/util/ds_depchain.h>


namespace Hako
{
	namespace Dummy
	{
		class GfxManager
		{
		public:
			typedef Hako::DS::DependencyChain<Hako::Gfx::RenderOperation*>::Reference RenderOperationReference;


			Hako::Error init();

			virtual Hako::Error internal_init()
				{ return Hako::Error::ok(); }

			virtual Hako::Error show()
				{ return Hako::Error::ok(); }

			virtual Hako::Error shutdown()
				{ return Hako::Error::ok(); }

			RenderOperationReference add_operation    (Hako::Gfx::RenderOperation* scene);
			void                     remove_operation (RenderOperationReference& ref);

		protected:
			Hako::DS::DependencyChain<Hako::Gfx::RenderOperation*> operations;
		};
	}
}


#endif
