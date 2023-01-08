#include "Matrix3.h"

BEGIN_OGS_NAMESPACE

const Matrix3& Matrix3::Identity()
{
	static Matrix3 s_indentity;

	return s_indentity;
}

Matrix3::Matrix3()
{
	memset(values, 0, sizeof(values));
	_11 = _22 = _33 = 1.0f;
}

END_OGS_NAMESPACE