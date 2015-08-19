#ifndef HAKO_UTIL_MATH_VECTOR_H
#define HAKO_UTIL_MATH_VECTOR_H


namespace Hako
{
	namespace Math
	{
		template <int N>
		class Vector
		{
		public:
			float element[N];

			Vector()          { for (int i = 0; i < N; i++) element[i] = 0;   }
			Vector(float val) { for (int i = 0; i < N; i++) element[i] = val; }
		};
	}
}


#endif
