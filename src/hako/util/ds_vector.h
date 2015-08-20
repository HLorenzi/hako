#ifndef HAKO_UTIL_DS_VECTOR_H
#define HAKO_UTIL_DS_VECTOR_H


#include <hako/util/debug.h>
#include <hako/util/allocator.h>


namespace Hako
{
	Hako::Allocator singleton_allocator();


	namespace DS
	{
		// A contiguous-memory list data structure.
		template <typename T>
		class Vector
		{
		public:
			Vector()
			{
			#ifdef HAKO_BUILD_DEBUG
				this->initialized = false;
			#endif
			}


			~Vector()
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				this->allocator.free.call(this->data);
				this->data = nullptr;
			}


			// Initializes the vector storage with the engine's allocator.
			void init()
			{
				HAKO_ASSERT(!this->initialized, "init() has already been called");
				this->allocator        = Hako::singleton_allocator();
				this->data             = nullptr;
				this->element_capacity = 0;
				this->element_num      = 0;
			#ifdef HAKO_BUILD_DEBUG
				this->initialized = true;
			#endif
			}


			// Initializes the vector storage with a custom allocator.
			void init_custom(Hako::Allocator allocator)
			{
				HAKO_ASSERT(!this->initialized, "init() has already been called");
				this->allocator        = allocator;
				this->data             = nullptr;
				this->element_capacity = 0;
				this->element_num      = 0;
			#ifdef HAKO_BUILD_DEBUG
				this->initialized = true;
			#endif
			}


			// Retrieves the raw pointer to storage.
			T* data_ptr()
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				return this->data;
			}


			// Retrieves the number of elements stored.
			unsigned int length()
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				return this->element_num;
			}


			// Retrieves a reference to an element at the given position.
			T& operator [] (const unsigned int index)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				HAKO_ASSERT(index < this->element_num, "index out of range");
				return this->data[index];
			}


			// Appends an element to the end of the list, growing the storage space
			// if necessary.
			unsigned int add(T element)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				this->ensure_capacity(this->element_num + 1);
				this->data[this->element_num] = element;
				this->element_num += 1;
				return this->element_num - 1;
			}


			unsigned int insert(T element, unsigned int before_position)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				this->ensure_capacity(this->element_num + 1);

				for (int i = this->element_num; i > before_position; i--)
					this->data[i] = this->data[i - 1];

				this->data[before_position] = element;
				this->element_num += 1;
				return before_position;
			}


			// Ensures that the vector's capacity is larger than or equal to
			// the given value, growing the storage space if necessary.
			void ensure_capacity(const unsigned int capacity)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				if (capacity > this->element_capacity)
				{
					this->allocator.reallocate.call(
						(void**)&this->data,
						sizeof(T) * this->element_capacity,
						32,
						sizeof(T) * capacity,
						32);

					this->element_capacity = capacity;
				}
			}


			// Sets the number of elements to the given value, growing the
			// storage space if necessary.
			void set_length(const unsigned int length)
			{
				HAKO_ASSERT(this->initialized, "init() must be called before");
				this->ensure_capacity(length);
				this->element_num = length;
			}


		protected:
		#ifdef HAKO_BUILD_DEBUG
			bool initialized;
		#endif

			T*           data;
			unsigned int element_num;
			unsigned int element_capacity;

			Hako::Allocator allocator;
		};
	}
}


#endif


