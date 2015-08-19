#ifndef HAKO_UTIL_DS_FLATTREE_H
#define HAKO_UTIL_DS_FLATTREE_H


#include <hako/util/ds_vector.h>


namespace Hako
{
	namespace DS
	{
		template <typename T>
		class FlatTree
		{
		protected:
			typedef unsigned int IdentifierType;


		public:
			class Reference
			{
				friend class FlatTree<T>;


				static Reference make_null()
				{
					Reference refer;
					refer.item_identifier = 0;
					refer.cached_index    = 0;
					return refer;
				}


			protected:
				IdentifierType item_identifier;
				unsigned int   cached_index;
			};


			class Node
			{
				friend class FlatTree<T>;


			protected:
				T            data;
				Reference    parent;
				unsigned int child_number;
			};


			FlatTree()
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

				Node node;
				node.data         = data;
				node.parent       = Reference::make_null();
				node.child_number = 0;

				unsigned int item_position = this->items.add(node);
				this->identifiers.add(this->get_next_identifier());

				return this->make_reference(item_position);
			}


			Reference add_child(Reference& parent, T data)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");

				Node node;
				node.data         = data;
				node.parent       = Reference::make_null();
				node.child_number = 0;

				this->refresh_reference(&parent);
				unsigned int item_position = this->find_next_sibling(parent.cached_index);

				this->items[parent.cached_index].child_number += 1;

				this->items.insert(node, item_position);
				this->identifiers.insert(this->get_next_identifier(), item_position);

				return this->make_reference(item_position);
			}


			T& operator [] (Reference& refer)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				HAKO_ASSERT(refer.item_identifier != 0, "trying to access null reference");
				this->refresh_reference(&refer);
				return this->items[refer.cached_index].data;
			}


		protected:
			IdentifierType get_next_identifier()
			{
				IdentifierType last_item_identifier = this->next_item_identifier;
				this->next_item_identifier += 1;
				HAKO_ASSERT(this->next_item_identifier > last_item_identifier, "item identifier overflow");
				return last_item_identifier;
			}


			Reference make_reference(unsigned int index)
			{
				Reference refer;
				refer.item_identifier   = this->identifiers[index];
				refer.cached_index      = index;
				return refer;
			}


			void refresh_reference(Reference* refer)
			{
                if (refer->item_identifier == 0)
					return;

				if (refer->cached_index < this->items.length() &&
					this->identifiers[refer->cached_index] == refer->item_identifier)
					return;

				for (int i = 0; i < this->identifiers.length(); i++)
				{
					if (this->identifiers[i] == refer->item_identifier)
					{
						refer->cached_index = i;
						return;
					}
				}

				HAKO_ERROR("reference points to a non-existent item");
			}


			unsigned int find_next_sibling(unsigned int index)
			{
				unsigned int result = index + 1;
				unsigned int count  = 0;
				while (count < this->items[index].child_number)
				{
					result = this->find_next_sibling(result);
					count += 1;
				}
				return result;
			}


		#ifdef HAKO_BUILD_DEBUG
			bool initialized;
		#endif
			Hako::DS::Vector<Node>           items;
			Hako::DS::Vector<IdentifierType> identifiers;

			unsigned int next_item_identifier;
		};
	}
}


#endif
