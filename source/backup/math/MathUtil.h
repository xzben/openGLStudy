#ifndef __2022_03_15_MATH_UTIL_H__
#define __2022_03_15_MATH_UTIL_H__

#include "math/Mat4.h"
#include "math/Vec3.h"
#include "math/quaternion.h"
#include "define.h"

BEGIN_NAMESPACE

#define MATRIX_SIZE (sizeof(float) * 16)

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
	static fMat4 lookAt(const fVec3& pos, const fVec3& target, const fVec3& up);
	//根据摄像头的 pos 和 rotation 计算 我们假设摄像头是默认  朝向屏幕内 -z 方向 (0, 0, -1), 然后通过摄像头节点的位移旋转得到摄像头真正的旋转方向，然后获得 view 矩阵
	static fMat4 cameraLookAt(const fVec3& pos, const fVec3& rot, const fVec3& up);

	static bool decompose(const fMat4& mat, fVec3* sc, Quaternion* rot, fVec3* translation);
	static float determinant(const fMat4& mat);

	static fMat4 createPerspective(float fieldOfView, float aspectRatio, float zNearPlane, float zFarPlane);

	static fMat4 createOrthographic(float width, float height, float zNearPlane, float zFarPlane);
	static fMat4 createOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);
};

END_NAMESPACE

#endif//__2022_03_15_MATH_UTIL_H__
