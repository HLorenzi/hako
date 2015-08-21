#include <hako/util/math_vector.h>


float Hako::Math::lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}


Hako::Math::Vector2 Hako::Math::lerp2(Vector2 a, Vector2 b, float t)
{
	return Vector2::make(
		lerp(a.x, b.x, t),
		lerp(a.y, b.y, t));
}


Hako::Math::Vector3 Hako::Math::lerp3(Vector3 a, Vector3 b, float t)
{
	return Vector3::make(
		lerp(a.x, b.x, t),
		lerp(a.y, b.y, t),
		lerp(a.z, b.z, t));
}


Hako::Math::Vector4 Hako::Math::lerp4(Vector4 a, Vector4 b, float t)
{
	return Vector4::make(
		lerp(a.x, b.x, t),
		lerp(a.y, b.y, t),
		lerp(a.z, b.z, t),
		lerp(a.w, b.w, t));
}


Hako::Math::Vector3 Hako::Math::slerp(Vector3 a, Vector3 b, float t)
{
	const float angle = acosf(a.dot(b));
	const float sinAngle = sinf(angle);
	if (fabsf(sinAngle) < 0.01f)
	{
		if (t < 0.5f) return a;
		else return b;
	}
	else
	{
		const float sinMTAngle = sinf((1.0f - t) * angle);
		const float sinTAngle = sinf(t * angle);
		const float invSinAngle = 1.0f / sinAngle;

		return a * (sinMTAngle * invSinAngle) + b * (sinTAngle * invSinAngle);
	}
}


Hako::Math::Matrix4 Hako::Math::Matrix4::make_zero()
{
	Matrix4 res;
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			res.cell[j][i] = 0;
	return res;
}


Hako::Math::Matrix4 Hako::Math::Matrix4::make_value(const float f)
{
	Matrix4 res;
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			res.cell[j][i] = f;
	return res;
}


Hako::Math::Matrix4 Hako::Math::Matrix4::make_array(const float m[4][4])
{
	Matrix4 res;
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			res.cell[j][i] = m[j][i];
	return res;
}


Hako::Math::Matrix4 Hako::Math::Matrix4::make_rotation_x(const float angle)
{
	const float mCos = cosf(angle);
	const float mSin = sinf(angle);
	const float cells[4][4] = {
		{ 1, 0, 0, 0 },
		{ 0, mCos, -mSin, 0 },
		{ 0, mSin, mCos, 0 },
		{ 0, 0, 0, 1 }
	};

	return Matrix4::make_array(cells);
}


Hako::Math::Matrix4 Hako::Math::Matrix4::make_rotation_y(const float angle)
{
	const float mCos = cosf(angle);
	const float mSin = sinf(angle);
	const float cells[4][4] = {
		{ mCos, 0, mSin, 0 },
		{ 0, 1, 0, 0 },
		{ -mSin, 0, mCos, 0 },
		{ 0, 0, 0, 1 }
	};

	return Matrix4::make_array(cells);
}


Hako::Math::Matrix4 Hako::Math::Matrix4::make_rotation_z(const float angle)
{
	const float mCos = cosf(angle);
	const float mSin = sinf(angle);
	const float cells[4][4] = {
		{ mCos, mSin, 0, 0 },
		{ -mSin, mCos, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	};

	return Matrix4::make_array(cells);
}


Hako::Math::Matrix4 Hako::Math::Matrix4::make_rotation(const Vector3 axis, const float rad)
{
	const float pCos = cosf(rad);
	const float pSin = sinf(rad);
	const float mCos = 1.0f - pCos;
	const float x = axis.x;
	const float y = axis.y;
	const float z = axis.z;

	const float cells[4][4] = {
		{ pCos + x * x * mCos, y * x * mCos + z * pSin, z * x * mCos - y * pSin, 0 },
		{ x * y * mCos - z * pSin, pCos + y * y * mCos, z * y * mCos + x * pSin, 0 },
		{ x * z * mCos + y * pSin, y * z * mCos - x * pSin, pCos + z * z * mCos, 0 },
		{ 0, 0, 0, 1 }
	};

	return Matrix4::make_array(cells);
}


Hako::Math::Matrix4 Hako::Math::Matrix4::make_translation(const float x, const float y, const float z) {
	const float cells[4][4] = {
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ x, y, z, 1 }
	};

	return Matrix4::make_array(cells);
}


Hako::Math::Matrix4 Hako::Math::Matrix4::make_scaling(const float x, const float y, const float z) {
	const float cells[4][4] = {
		{ x, 0, 0, 0 },
		{ 0, y, 0, 0 },
		{ 0, 0, z, 0 },
		{ 0, 0, 0, 1 }
	};

	return Matrix4::make_array(cells);
}


Hako::Math::Matrix4 Hako::Math::Matrix4::make_identity() {
	const float cells[4][4] = {
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	};

	return Matrix4::make_array(cells);
}


Hako::Math::Matrix4& Hako::Math::Matrix4::set_identity() {
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			cell[j][i] = (i == j);
		}
	}
	return *this;
}


Hako::Math::Matrix4 Hako::Math::Matrix4::make_orthographic(const float left, const float right, const float top, const float bottom, const float zNear, const float zFar)
{
	const float cells[4][4] = {
		{ 2.0f / (right - left), 0, 0, 0 },
		{ 0, 2.0f / (top - bottom), 0, 0 },
		{ 0, 0, -2.0f / (zFar - zNear), 0 },
		{ -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(zFar + zNear) / (zFar - zNear), 1 }
	};

	return Matrix4::make_array(cells) * Matrix4::make_scaling(1, -1, 1);
}


Hako::Math::Matrix4 Hako::Math::Matrix4::make_frustum(const float left, const float right, const float top, const float bottom, const float zNear, const float zFar)
{
	const float cells[4][4] = {
		{ 2 * zNear / (right - left), 0, 0, 0 },
		{ 0, 2 * zNear / (top - bottom), 0, 0 },
		{ (right + left) / (right - left), (top + bottom) / (top - bottom), -(zFar + zNear) / (zFar - zNear), -1 },
		{ 0, 0, -(2 * zFar * zNear) / (zFar - zNear), 0 }
	};

	return Matrix4::make_array(cells) * Matrix4::make_scaling(1, -1, 1);
}


Hako::Math::Matrix4 Hako::Math::Matrix4::make_perspective(const float yFov, const float aspectWidthByHeight, const float zNear, const float zFar)
{
	float fH = tanf(yFov / 2) * zNear;
	float fW = fH * aspectWidthByHeight;
	return Matrix4::make_frustum(-fW, fW, -fH, fH, zNear, zFar);
}


Hako::Math::Matrix4 Hako::Math::Matrix4::make_lookat(const Vector3 eye, const Vector3 target, const Vector3 up)
{
	Vector3 zaxis = (eye - target).get_normalized();
	Vector3 xaxis = up.cross(zaxis).get_normalized();
	Vector3 yaxis = zaxis.cross(xaxis);

	const float cells[4][4] = {
		{ xaxis.x, yaxis.x, zaxis.x, 0 },
		{ xaxis.y, yaxis.y, zaxis.y, 0 },
		{ xaxis.z, yaxis.z, zaxis.z, 0 },
		{ -xaxis.dot(eye), -yaxis.dot(eye), -zaxis.dot(eye), 1 }
	};

	return Matrix4::make_array(cells);
}


Hako::Math::Vector3 Hako::Math::Matrix4::operator * (const Vector3& v) const
{
	Vector3 res;
	res.x = (cell[0][0] * v.x) + (cell[0][1] * v.y) + (cell[0][2] * v.z) + (cell[0][3]);
	res.y = (cell[1][0] * v.x) + (cell[1][1] * v.y) + (cell[1][2] * v.z) + (cell[1][3]);
	res.z = (cell[2][0] * v.x) + (cell[2][1] * v.y) + (cell[2][2] * v.z) + (cell[2][3]);
	return res;
}


Hako::Math::Matrix4 Hako::Math::Matrix4::operator * (const Matrix4& m) const
{
	Matrix4 res = Matrix4::make_zero();
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 4; k++)
		{
			for (int i = 0; i < 4; i++)
			{
				res.cell[j][i] += m.cell[j][k] * cell[k][i];
			}
		}
	}
	return res;
}


Hako::Math::Matrix4& Hako::Math::Matrix4::operator *= (const Matrix4& m)
{
	Matrix4 res = Matrix4::make_zero();
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 4; k++)
		{
			for (int i = 0; i < 4; i++)
			{
				res.cell[j][i] += m.cell[j][k] * cell[k][i];
			}
		}
	}
	*this = res;
	return *this;
}
