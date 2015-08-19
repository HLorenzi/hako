#ifndef HAKO_UTIL_DS_DEPCHAIN_H
#define HAKO_UTIL_DS_DEPCHAIN_H


#include "refvector.h"
#include <hako/common/debug.h>


namespace Hako
{
	namespace DS
	{
		// A contiguous-memory list which allows setting dependencies
		// between items, which later can be used to calculate
		// the order of parallel computations.
		template <typename T>
		class DependencyChain : public Hako::DS::RefVector<T>
		{
		public:
			typedef typename RefVector<T>::Reference Reference;


		protected:
			class Dependency
			{
				friend class DependencyChain<T>;

			protected:
				Reference what_item;
				Reference depends_on;
			};


			class Exclusivity
			{
				friend class DependencyChain<T>;

			protected:
				Reference what_item;
				Reference is_exclusive_to;
			};


		public:
			void init_custom(const unsigned int capacity, Hako::Allocator allocator)
			{
				HAKO_ASSERT(!this->initialized, "init() was already called");

				this->Hako::DS::RefVector<T>:: init(capacity, allocator);
				this->dependency_list         .init(0, allocator);
				this->exclusivity_list        .init(0, allocator);

				HAKO_ONLYINDEBUG( this->initialized = true; )
			}


			Hako::DS::RefVector<Dependency>::Reference add_dependency(Reference what_item, Reference depends_on)
			{
				Dependency dep;
				dep.what_item  = what_item;
				dep.depends_on = depends_on;
				return this->dependency_list.add(dep);
			}


			Hako::DS::RefVector<Exclusivity>::Reference add_exclusivity(Reference what_item, Reference is_exclusive_to)
			{
				Exclusivity excl;
				excl.what_item       = what_item;
				excl.is_exclusive_to = is_exclusive_to;
				return this->exclusivity_list.add(excl);
			}


		protected:
			HAKO_ONLYINDEBUG( bool initialized = false; )

			Hako::DS::RefVector<Dependency>  dependency_list;
			Hako::DS::RefVector<Exclusivity> exclusivity_list;
		};
	}
}


#endif
