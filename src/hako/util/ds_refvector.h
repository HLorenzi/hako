#ifndef HAKO_UTIL_DS_REFVECTOR_H
#define HAKO_UTIL_DS_REFVECTOR_H


#include <hako/util/ds_vector.h>


namespace Hako
{
	namespace DS
	{
		template <typename T>
		class RefVector
		{
		protected:
			typedef unsigned int IdentifierType;


		public:
			class Reference
			{
			public:
				friend class RefVector<T>;


				static Reference make_null()
				{
					Reference refer;
					refer.item_identifier = 0;
					refer.cached_index    = 0;
					return refer;
				}


				void invalidate()
				{
					this->item_identifier = 0;
					this->cached_index    = 0;
				}


				bool is_invalid()
				{
					return (this->item_identifier == 0);
				}


				bool is_valid()
				{
					return (!this->is_invalid());
				}


				IdentifierType item_identifier;
				unsigned int   cached_index;
			};


			RefVector()
			{
			#ifdef HAKO_BUILD_DEBUG
				this->initialized = false;
			#endif
			}


			void init()
			{
				HAKO_ASSERT(!this->initialized, "init() has already been called");

				this->next_item_identifier = 1;

				this->items       .init();
				this->identifiers .init();

			#ifdef HAKO_BUILD_DEBUG
				this->initialized = true;
			#endif
			}


			Reference add(T data)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");

				unsigned int item_position = this->items.add(data);
				this->identifiers.add(this->get_next_identifier());

				return this->make_reference(item_position);
			}


			Reference insert(T data, unsigned int before_position)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				HAKO_ASSERT(before_position <= this->length(), "index out of bounds");

				this->items.insert(data, before_position);
				this->identifiers.insert(this->get_next_identifier(), before_position);

				return this->make_reference(before_position);
			}


			void remove(Reference& ref)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				HAKO_ASSERT(!ref.is_invalid(), "reference is invalid");
				this->refresh_reference(&ref);
				this->items      .remove(ref.cached_index);
				this->identifiers.remove(ref.cached_index);
				ref.invalidate();
			}


			unsigned int length()
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				return this->items.length();
			}


			T& operator [] (Reference& refer)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				HAKO_ASSERT(refer.item_identifier != 0, "trying to access null reference");
				this->refresh_reference(&refer);
				return this->items[refer.cached_index];
			}


			T& get_by_index(unsigned int index)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				HAKO_ASSERT(index < this->length(), "index out of bounds");
				return this->items[index];
			}


			Reference make_reference(unsigned int index)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				HAKO_ASSERT(index < this->length(), "index out of bounds");
				Reference refer;
				refer.item_identifier = this->identifiers[index];
				refer.cached_index    = index;
				return refer;
			}


			void refresh_reference(Reference* refer)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				HAKO_ASSERT(refer != nullptr, "reference must not be null");

                if (refer->item_identifier == 0)
					return;

				if (refer->cached_index < this->length() &&
					this->identifiers[refer->cached_index] == refer->item_identifier)
					return;

				for (int i = 0; i < this->length(); i++)
				{
					if (this->identifiers[i] == refer->item_identifier)
					{
						refer->cached_index = i;
						return;
					}
				}

				HAKO_ERROR("reference points to a non-existent item");
			}


		protected:
			IdentifierType get_next_identifier()
			{
				IdentifierType last_item_identifier = this->next_item_identifier;
				this->next_item_identifier += 1;
				HAKO_ASSERT(this->next_item_identifier > last_item_identifier, "item identifier overflow");
				return last_item_identifier;
			}


		#ifdef HAKO_BUILD_DEBUG
			bool initialized;
		#endif
			Hako::DS::Vector<T>              items;
			Hako::DS::Vector<IdentifierType> identifiers;

			IdentifierType next_item_identifier;
		};
	}
}


#endif
