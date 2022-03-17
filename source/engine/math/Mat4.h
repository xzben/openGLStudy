/*
	行主序矩阵，列主序矩阵 指的是矩阵存储的内存分布是以行排序还是以列排序的

	   行主序				列主序
	0  1  2  3           0  4  8   12
	4  5  6  7			 1  5  9   13
	8  9  10 11          2  6  10  14
	12 13 14 15          3  7  11  15

	openGL API 接受的是列主序的的矩阵，如果一个OpenGL
*/

#ifndef __2022_01_05_MATRIX_4_4_H__
#define __2022_01_05_MATRIX_4_4_H__

#include "Vec4.h"

//列主序矩阵
template<class TYPENAME>
class Mat4
{
public:
	TYPENAME m_data[16];

	Mat4() {
		reset();
	}

	void reset() {
		// 第一列
		m_data[0] = 1;
		m_data[1] = 0;
		m_data[2] = 0;
		m_data[3] = 0;

		//第二列
		m_data[4] = 0;
		m_data[5] = 1;
		m_data[6] = 0;
		m_data[7] = 0;

		//第三列
		m_data[8] = 0;
		m_data[9] = 0;
		m_data[10] = 1;
		m_data[11] = 0;

		//第四列
		m_data[12] = 0;
		m_data[13] = 0;
		m_data[14] = 0;
		m_data[15] = 1;
	}
	Mat4(	TYPENAME m11, TYPENAME m12, TYPENAME m13, TYPENAME m14, 
			TYPENAME m21, TYPENAME m22, TYPENAME m23, TYPENAME m24, 
			TYPENAME m31, TYPENAME m32, TYPENAME m33, TYPENAME m34, 
			TYPENAME m41, TYPENAME m42, TYPENAME m43, TYPENAME m44) 
	{
		m_data[0] = m11;
		m_data[1] = m21;
		m_data[2] = m31;
		m_data[3] = m41;

		m_data[4] = m12;
		m_data[5] = m22;
		m_data[6] = m32;
		m_data[7] = m42;

		m_data[8] = m13;
		m_data[9] = m23;
		m_data[10] = m33;
		m_data[11] = m43;

		m_data[12] = m14;
		m_data[13] = m24;
		m_data[14] = m34;
		m_data[15] = m44;
	}

	~Mat4() {

	}

	void operator+(const TYPENAME& val) {
		for (int i = 0; i < 16; i++)
			m_data[i] += val;
	}

	void operator-(const TYPENAME& val) {
		for (int i = 0; i < 16; i++)
			m_data[i] -= val;
	}

	void operator*(const TYPENAME& val) {
		for (int i = 0; i < 16; i++)
			m_data[i] *= val;
	}

	Mat4<TYPENAME> operator*(const Mat4<TYPENAME>& rvalue) const {
		Mat4<TYPENAME> result;

		result.m_data[0]   = m_data[0] * rvalue.m_data[0]  + m_data[4] * rvalue.m_data[1]  + m_data[8] * rvalue.m_data[2]  + m_data[12]*rvalue.m_data[3];
		result.m_data[4]   = m_data[0] * rvalue.m_data[4]  + m_data[4] * rvalue.m_data[5]  + m_data[8] * rvalue.m_data[6]  + m_data[12] * rvalue.m_data[7];
		result.m_data[8]   = m_data[0] * rvalue.m_data[8]  + m_data[4] * rvalue.m_data[9]  + m_data[8] * rvalue.m_data[10] + m_data[12] * rvalue.m_data[11];
		result.m_data[12]  = m_data[0] * rvalue.m_data[12] + m_data[4] * rvalue.m_data[13] + m_data[8] * rvalue.m_data[14] + m_data[12] * rvalue.m_data[15];

		result.m_data[1]   = m_data[1] * rvalue.m_data[0]  + m_data[5] * rvalue.m_data[1]  + m_data[9] * rvalue.m_data[2]  + m_data[13] * rvalue.m_data[3];
		result.m_data[5]   = m_data[1] * rvalue.m_data[4]  + m_data[5] * rvalue.m_data[5]  + m_data[9] * rvalue.m_data[6]  + m_data[13] * rvalue.m_data[7];
		result.m_data[9]   = m_data[1] * rvalue.m_data[8]  + m_data[5] * rvalue.m_data[9]  + m_data[9] * rvalue.m_data[10] + m_data[13] * rvalue.m_data[11];
		result.m_data[13]  = m_data[1] * rvalue.m_data[12] + m_data[5] * rvalue.m_data[13] + m_data[9] * rvalue.m_data[14] + m_data[13] * rvalue.m_data[15];

		result.m_data[2]   = m_data[2] * rvalue.m_data[0]  + m_data[6] * rvalue.m_data[1]  + m_data[10] * rvalue.m_data[2]  + m_data[14] * rvalue.m_data[3];
		result.m_data[6]   = m_data[2] * rvalue.m_data[4]  + m_data[6] * rvalue.m_data[5]  + m_data[10] * rvalue.m_data[6]  + m_data[14] * rvalue.m_data[7];
		result.m_data[10]  = m_data[2] * rvalue.m_data[8]  + m_data[6] * rvalue.m_data[9]  + m_data[10] * rvalue.m_data[10] + m_data[14] * rvalue.m_data[11];
		result.m_data[14]  = m_data[2] * rvalue.m_data[12] + m_data[6] * rvalue.m_data[13] + m_data[10] * rvalue.m_data[14] + m_data[14] * rvalue.m_data[15];

		result.m_data[3]   = m_data[3] * rvalue.m_data[0]  + m_data[7] * rvalue.m_data[1]  + m_data[11] * rvalue.m_data[2]  + m_data[15] * rvalue.m_data[3];
		result.m_data[7]   = m_data[3] * rvalue.m_data[4]  + m_data[7] * rvalue.m_data[5]  + m_data[11] * rvalue.m_data[6]  + m_data[15] * rvalue.m_data[7];
		result.m_data[11]  = m_data[3] * rvalue.m_data[8]  + m_data[7] * rvalue.m_data[9]  + m_data[11] * rvalue.m_data[10] + m_data[15] * rvalue.m_data[11];
		result.m_data[15]  = m_data[3] * rvalue.m_data[12] + m_data[7] * rvalue.m_data[13] + m_data[11] * rvalue.m_data[14] + m_data[15] * rvalue.m_data[15];

		return result;
	}

	Vec4<TYPENAME> operator*(const Vec4<TYPENAME>& rvalue) const {
		Vec4<TYPENAME> result;

		result.x = m_data[0] * rvalue.x + m_data[4] * rvalue.y + m_data[8] * rvalue.z + m_data[12] * rvalue.w;
		result.y = m_data[1] * rvalue.x + m_data[5] * rvalue.y + m_data[9] * rvalue.z + m_data[13] * rvalue.w;
		result.z = m_data[2] * rvalue.x + m_data[6] * rvalue.y + m_data[10] * rvalue.z + m_data[14] * rvalue.w;
		result.w = m_data[3] * rvalue.x + m_data[7] * rvalue.y + m_data[11] * rvalue.z + m_data[15] * rvalue.w;

		return result;
	}
};

typedef Mat4<float> fMat4;
typedef Mat4<int> iMat4;

#endif//__2022_01_05_MATRIX_4_4_H__