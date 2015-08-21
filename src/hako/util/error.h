#ifndef HAKO_UTIL_ERROR_H
#define HAKO_UTIL_ERROR_H


namespace Hako
{
	enum class ErrorClass
	{
		NoError,
		Unknown,
		Unsupported
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


		static Error unknown()
		{
			return Hako::Error::make(Hako::ErrorClass::Unknown);
		}


		static Error unsupported()
		{
			return Hako::Error::make(Hako::ErrorClass::Unsupported);
		}


		bool is_ok()
		{
			return (error_class == Hako::ErrorClass::NoError);
		}


		ErrorClass error_class;


	protected:
		Error() { }
	};
}


#endif
