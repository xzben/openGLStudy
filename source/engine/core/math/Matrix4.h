#pragma once
/*
	列矩阵
*/
#include "define.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaterion.h"

BEGIN_OGS_NAMESPACE

class Matrix4
{
public:
	static const Matrix4 Identity;

	static Matrix4 translate(const Vector3& tans);
	static Matrix4 scale(const Vector3& sc);
	static Matrix4 rotation(const Vector3& rot);
	static Matrix4 rotation(const Quaterion& rot);
	static Matrix4 perspective(float fieldOfView, float aspectRatio, float znear, float zfar);
	static Matrix4 orthograhic(float width, float height, float znear, float zfar);
	static Matrix4 orthograhic(float left, float right, float bottom, float top, float znear, float zfar);
	static Matrix4 lookAt(const Vector3& pos, const Vector3& target, const Vector3& up);
public:
	Matrix4();
	Matrix4(float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44);

	bool decompose(Vector3* trans, Vector3* scale, Quaterion* q) const;
	float determinant() const; //矩阵行列式

	const Matrix4& operator+=(const float v);
	const Matrix4& operator-=(const float v);
	const Matrix4& operator*=(const float v);

	Matrix4 operator+(const float v);
	Matrix4 operator-(const float v);
	Matrix4 operator*(const float v);
	Matrix4 operator*(const Matrix4& rhs);
	const Matrix4& operator*=(const Matrix4& rhs);
	Vector3 operator*(const Vector3& rhs);
	Vector4 operator*(const Vector4& rhs);
	Matrix4 transpose()const; //矩阵转置
	Matrix4 inverse()const; //矩阵的逆

private:
	union
	{
		struct
		{
			float _11, _21, _31, _41;
			float _12, _22, _32, _42;
			float _13, _23, _33, _43;
			float _14, _24, _34, _44;
		};
		float values[16];
	};
};
END_OGS_NAMESPACE