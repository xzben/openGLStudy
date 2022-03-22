#ifndef __2022_03_17_QUATERNION_H__
#define __2022_03_17_QUATERNION_H__
#include "math/Vec3.h"
#include "math/Mat4.h"
#include "common.h"

BEGIN_NAMESPACE
class Quaternion
{
public:
	static const Quaternion& identity();
	static const Quaternion& zero();
	static void createFromAxisAngle(const fVec3& axis, float angle, Quaternion* dst);
	static void createFromRotationMatrix(const fMat4& m, Quaternion* dst);
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion();
	Quaternion(float xx, float yy, float zz, float ww);
	Quaternion(const fVec3& axis, float angle);
	Quaternion(const fMat4& m);
	Quaternion(const Quaternion& q);
	~Quaternion();

	void set(const fVec3& axis, float angle);
	void set(const fMat4& m);
	void set(const Quaternion& q);

	bool isIdentity();
	void setIdentity();
	bool isZero();
	void normalize();
	Quaternion getNormalized()const;

	//¹²éî
	void conjugate();
	Quaternion getConjugated() const;
	float toAxisAngle(fVec3* axis) const;

	void lerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
	void slerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
	void squad(const Quaternion& q1, const Quaternion& q2, const Quaternion& s1, const Quaternion& s2, float t, Quaternion* dst);
	void slerp(float q1x, float q1y, float q1z, float q1w, float q2x, float q2y, float q2z, float q2w, float t, float* dstx, float* dsty, float* dstz, float* dstw);
	void slerpForSquad(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
};

END_NAMESPACE

#endif//__2022_03_17_QUATERNION_H__
