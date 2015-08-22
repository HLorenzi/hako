#ifndef PKTR_UTIL_MATH_VECTOR_H
#define PKTR_UTIL_MATH_VECTOR_H


#include <math.h>


namespace Hako
{
	namespace Math
	{
		class Vector2
		{
		public:
			float x, y;

			static Vector2 make(float pX, float pY) { Vector2 v; v.x = pX; v.y = pY; return v; }

			const Vector2&	operator += (const Vector2& v)			{ x += v.x; y += v.y; return *this; }
			Vector2			operator +  (const Vector2& v) const	{ return Vector2::make(x + v.x, y + v.y); }
			const Vector2&	operator -= (const Vector2& v)			{ x -= v.x; y -= v.y; return *this; }
			const Vector2&	operator *= (float f)					{ x *= f; y *= f; return *this; }
			Vector2			operator *  (float f) const				{ return Vector2::make(x * f, y * f); }

			float length() const { return sqrtf(x * x + y * y); }
			void normalize() { float len = length(); if (len != 0) { x /= len; y /= len; } }
			Vector2 get_normalized() const { float len = length(); if (len != 0) return Vector2::make(x / len, y / len); else return Vector2::make(0, 0); }
		};


		class Vector3
		{
		public:
			float x, y, z;

			static Vector3 make(float pX, float pY, float pZ) { Vector3 v; v.x = pX; v.y = pY; v.z = pZ; return v; }

			const Vector3&	operator += (const Vector3& v)			{ x += v.x; y += v.y; z += v.z; return *this; }
			const Vector3&	operator += (const Vector2& v)			{ x += v.x; y += v.y; return *this; }
			Vector3			operator +  (const Vector3& v) const	{ return Vector3::make(x + v.x, y + v.y, z + v.z); }
			Vector3			operator -  (const Vector3& v) const	{ return Vector3::make(x - v.x, y - v.y, z - v.z); }
			Vector3			operator *  (float f) const				{ return Vector3::make(x * f, y * f, z * f); }
			Vector3			operator /  (float f) const				{ return Vector3::make(x / f, y / f, z / f); }

			float length() const { return sqrtf(x * x + y * y + z * z); }
			void normalize() { float len = length(); if (len != 0) { x /= len; y /= len; z /= len; } }
			Vector3 get_normalized() const { float len = length(); if (len != 0) return Vector3::make(x / len, y / len, z / len); else return Vector3::make(0, 0, 0); }
			float dot(const Vector3& other) const { return x * other.x + y * other.y + z * other.z; }
			Vector3 cross(const Vector3& other) const { return Vector3::make(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }
		};


		class Vector4
		{
		public:
			float x, y, z, w;

			static Vector4 make(float pX, float pY, float pZ, float pW) { Vector4 v; v.x = pX; v.y = pY; v.z = pZ; v.w = pW; return v; }

			const Vector4&	operator += (const Vector4& v)			{ x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
			Vector4			operator +  (const Vector4& v) const	{ return Vector4::make(x + v.x, y + v.y, z + v.z, w + v.w); }
			Vector4			operator -  (const Vector4& v) const	{ return Vector4::make(x - v.x, y - v.y, z - v.z, w - v.w); }
			Vector4			operator /  (float f) const				{ return Vector4::make(x / f, y / f, z / f, w / f); }

			float length() const { return sqrtf(x * x + y * y + z * z + w * w); }
			void normalize() { float len = length(); if (len != 0) { x /= len; y /= len; z /= len; w /= len; } }
			Vector4 get_normalized() const { float len = length(); if (len != 0) return Vector4::make(x / len, y / len, z / len, w / len); else return Vector4::make(0, 0, 0, 0); }
		};


		class Color
		{
		public:
			float r, g, b, a;

			static Color make(float rr, float gg, float bb, float aa) { Color c; c.r = rr; c.g = gg; c.b = bb; c.a = aa; return c; }
		};


		class alignas(16) Matrix4
		{
		public:
			float cell[4][4];

			static Matrix4  make_zero();
			static Matrix4  make_identity();
			static Matrix4  make_value(const float f);
			static Matrix4  make_array(const float m[4][4]);
			static Matrix4  make_rotation_x(const float rad);
			static Matrix4  make_rotation_y(const float rad);
			static Matrix4  make_rotation_z(const float rad);
			static Matrix4  make_rotation(const Vector3 axis, const float rad);
			static Matrix4  make_translation(const Vector3 translation);
			static Matrix4  make_scaling(const Vector3 scale);
			static Matrix4  make_orthographic(const float left, const float right, const float top, const float bottom, const float zNear, const float zFar);
			static Matrix4  make_frustum(const float left, const float right, const float top, const float bottom, const float zNear, const float zFar);
			static Matrix4  make_perspective(const float yFov, const float aspectWidthByHeight, const float zNear, const float zFar);
			static Matrix4  make_lookat(const Vector3 eye, const Vector3 target, const Vector3 up);

			Matrix4& set_identity();

			Vector3  operator *  (const Vector3& v) const;
			Matrix4  operator *  (const Matrix4& m) const;
			Matrix4& operator *= (const Matrix4& m);
		};


		extern float pi;

		float   lerp(float a, float b, float t);
		Vector2 lerp2(Vector2 a, Vector2 b, float t);
		Vector3 lerp3(Vector3 a, Vector3 b, float t);
		Vector4 lerp4(Vector4 a, Vector4 b, float t);
		Vector3 slerp(Vector3 a, Vector3 b, float t);

		float deg_to_rad(float deg);
		float rad_to_deg(float deg);
	}
}

#endif
