#ifndef __2022_03_15_MATH_UTIL_H__
#define __2022_03_15_MATH_UTIL_H__

#include "math/Mat4.h"
#include "math/Vec3.h"
#include "math/quaternion.h"

#define CC_DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f) // PI / 180
#define CC_RADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) * 57.29577951f) // PI * 180

class MathUtil
{
public:
	static fMat4 translate(const fVec3& mov);
	static fMat4 translate(const float& x, const float& y, const float& z);
	static fMat4 scale(const fVec3& sc);
	static fMat4 scale(float sc);
	static fMat4 scale(const float& x, const float& y, const float& z);

	static const fMat4& IdentityMat4();
	static fMat4 rotation(const fVec3& rot);
	static fMat4 rotation(const float& x, const float& y, const float& z);
	static fMat4 rotation(const Quaternion& q);


	//计算摄像机的 view 矩阵 pos 摄像机位置 target 摄像机对着的目标位置  up 上向量
	static fMat4 lookAt(fVec3 pos, fVec3 target, fVec3 up);

	static bool decompose(const fMat4& mat, fVec3* sc, Quaternion* rot, fVec3* translation);
	static float determinant(const fMat4& mat);
};
#endif//__2022_03_15_MATH_UTIL_H__
