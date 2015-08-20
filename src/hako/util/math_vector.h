#ifndef HAKO_UTIL_MATH_VECTOR_H
#define HAKO_UTIL_MATH_VECTOR_H


namespace Hako
{
	namespace Math
	{
		class Vector2
		{
		public:
			float x, y;
		};


		class Vector3
		{
		public:
			float x, y, z;
		};


		class Matrix4
		{
		public:
			float cells[4][4];
		};
	}
}


#endif
