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

	//����������� view ���� pos �����λ�� target ��������ŵ�Ŀ��λ��  up ������
	static fMat4 lookAt(const fVec3& pos, const fVec3& target, const fVec3& up);
	//��������ͷ�� pos �� rotation ���� ���Ǽ�������ͷ��Ĭ��  ������Ļ�� -z ���� (0, 0, -1), Ȼ��ͨ������ͷ�ڵ��λ����ת�õ�����ͷ��������ת����Ȼ���� view ����
	static fMat4 cameraLookAt(const fVec3& pos, const fVec3& rot, const fVec3& up);

	static bool decompose(const fMat4& mat, fVec3* sc, Quaternion* rot, fVec3* translation);
	static float determinant(const fMat4& mat);

	static fMat4 createPerspective(float fieldOfView, float aspectRatio, float zNearPlane, float zFarPlane);

	static fMat4 createOrthographic(float width, float height, float zNearPlane, float zFarPlane);
	static fMat4 createOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);
};

END_NAMESPACE

#endif//__2022_03_15_MATH_UTIL_H__
