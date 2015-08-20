#ifndef HAKO_UTIL_ERROR_H
#define HAKO_UTIL_ERROR_H


namespace Hako
{
	enum class ErrorClass
	{
		NoError,
		Unknown,
		OutOfMemory,
		OutOfResources,
		InvalidOperation
	};


	class Error
	{
	public:
		static Error make(Hako::ErrorClass error_class)
		{
			Error err;
			err.error_class = error_class;
			return err;
		}


		static Error ok()
		{
			return Hako::Error::make(Hako::ErrorClass::NoError);
		}


		ErrorClass error_class;


	protected:
		Error() { }
	};
}


#endif
