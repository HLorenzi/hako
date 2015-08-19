#ifndef HAKO_UTIL_CALLBACK_H
#define HAKO_UTIL_CALLBACK_H


#include <hako/util/debug.h>


namespace Hako
{
	template <typename TReturn, typename... TArgs>
	class Callback
	{
	public:
		template <typename TObject, TReturn (TObject::*member_function)(TArgs...)>
		static Callback<TReturn, TArgs...> make_member(TObject* user_data)
		{
			Callback<TReturn, TArgs...> callback;
			callback.user_data    = (void*)user_data;
			callback.wrapped_call = wrapped_member_call<TObject, member_function>;
			return callback;
		}


		template <typename TObject, TReturn (*static_function)(TObject*, TArgs...)>
		static Callback<TReturn, TArgs...> make_userdata(TObject* user_data)
		{
			Callback<TReturn, TArgs...> callback;
			callback.user_data    = (void*)user_data;
			callback.wrapped_call = wrapped_userdata_call<TObject, static_function>;
			return callback;
		}


		template <TReturn (*static_function)(TArgs...)>
		static Callback<TReturn, TArgs...> make_static()
		{
			Callback<TReturn, TArgs...> callback;
			callback.user_data    = nullptr;
			callback.wrapped_call = wrapped_static_call<static_function>;
			return callback;
		}


		TReturn call(TArgs... args)
		{
			return this->wrapped_call(this->user_data, args...);
		}


	protected:
		TReturn(*wrapped_call)(void*, TArgs...);
		void* user_data;


		template <typename TObject, TReturn (TObject::*member_function)(TArgs...)>
		static TReturn wrapped_member_call(void* user_data, TArgs... args)
		{
			return (((TObject*)user_data)->*member_function)(args...);
		}


		template <typename TObject, TReturn (*static_function)(TObject*, TArgs...)>
		static TReturn wrapped_userdata_call(void* user_data, TArgs... args)
		{
			return static_function((TObject*)user_data, args...);
		}


		template <TReturn (*static_function)(TArgs...)>
		static TReturn wrapped_static_call(void* user_data, TArgs... args)
		{
			HAKO_UNUSED(user_data);
			return static_function(args...);
		}
	};
}


#endif
