#include "Quaterion.h"

BEGIN_OGS_NAMESPACE

Quaterion::Quaterion()
	:x(0.f), y(0.f), z(0.f), w(1.f)
{

}
Quaterion::Quaterion(float ww, float xx, float yy, float zz)
	: w(ww), x(xx), y(yy), z(zz)
{

}

Quaterion::Quaterion(const Vector3& axis, float angle)
{
	float halfAngle = CC_DEGREES_TO_RADIANS(angle);
	float sinHalfAngle = sinf(halfAngle);

	Vector3 normal(axis);
	normal.normalize();

	x = normal.x * sinHalfAngle;
	y = normal.x * sinHalfAngle;
	z = normal.x * sinHalfAngle;
	w = cosf(halfAngle);
}

Quaterion::Quaterion(const Quaterion& q)
{
	memcpy(values, q.values, sizeof(values));
}

void Quaterion::normalize()
{
	float n = x * x + y * y + z * z + w * w;

	// Already normalized.
	if (n == 1.0f)
		return;

	n = std::sqrt(n);
	// Too close to zero.
	if (n < 0.000001f)
		return;

	n = 1.0f / n;
	x *= n;
	y *= n;
	z *= n;
	w *= n;
}
bool Quaterion::isZero() const
{
	return x == 0.f && y == 0.f && z == 0.f && w == 0.f;
}

void Quaterion::setIndentity()
{
	x = y = z = 0.f;
	w = 1.f;
}

bool Quaterion::isIndentity() const
{
	return x == 0.f && y == 0.f && z == 0.f && w == 1.f;
}
END_OGS_NAMESPACE