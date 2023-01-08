#pragma once

#include "define.h"
#include "Vector3.h"

BEGIN_OGS_NAMESPACE

class Quaterion
{
public:
	Quaterion();
	Quaterion(float ww, float xx, float yy, float zz);
	Quaterion(const Vector3& axis, float angle);
	Quaterion(const Quaterion& q);

	void normalize();
	bool isZero() const;
	void setIndentity();
	bool isIndentity() const;

public:
	union
	{
		struct  
		{
			float w, x, y, z;
		};

		float values[4];
	};

};
END_OGS_NAMESPACE