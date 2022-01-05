#ifndef __2022_01_05_MATRIX_4_4_H__
#define __2022_01_05_MATRIX_4_4_H__

#include "Vec4.h"

template<class TYPENAME>
class Mat4
{
public:
	TYPENAME m_data[16];

	Mat4() {
		m_data[0] = 1;
		m_data[1] = 0;
		m_data[2] = 0;
		m_data[3] = 0;

		m_data[4] = 0;
		m_data[5] = 1;
		m_data[6] = 0;
		m_data[7] = 0;

		m_data[8] = 0;
		m_data[9] = 0;
		m_data[10] = 1;
		m_data[11] = 0;

		m_data[12] = 0;
		m_data[13] = 0;
		m_data[14] = 0;
		m_data[15] = 1;
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

	Mat4<TYPENAME> operator*(const Mat4<TYPENAME>& rvalue) {
		Mat4<TYPENAME> result;

		result.m_data[0] = m_data[0] * rvalue.m_data[0] + m_data[1] * rvalue.m_data[4] + m_data[2] * rvalue.m_data[8] + m_data[3]*rvalue.m_data[12];
		result.m_data[1] = m_data[0] * rvalue.m_data[1] + m_data[1] * rvalue.m_data[5] + m_data[2] * rvalue.m_data[9] + m_data[3] * rvalue.m_data[13];
		result.m_data[2] = m_data[0] * rvalue.m_data[2] + m_data[1] * rvalue.m_data[6] + m_data[2] * rvalue.m_data[10] + m_data[3] * rvalue.m_data[14];
		result.m_data[3] = m_data[0] * rvalue.m_data[3] + m_data[1] * rvalue.m_data[7] + m_data[2] * rvalue.m_data[11] + m_data[3] * rvalue.m_data[15];

		result.m_data[4] = m_data[4] * rvalue.m_data[0] + m_data[5] * rvalue.m_data[4] + m_data[6] * rvalue.m_data[8] + m_data[7] * rvalue.m_data[12];
		result.m_data[5] = m_data[4] * rvalue.m_data[1] + m_data[5] * rvalue.m_data[5] + m_data[6] * rvalue.m_data[9] + m_data[7] * rvalue.m_data[13];
		result.m_data[6] = m_data[4] * rvalue.m_data[2] + m_data[5] * rvalue.m_data[6] + m_data[6] * rvalue.m_data[10] + m_data[7] * rvalue.m_data[14];
		result.m_data[7] = m_data[4] * rvalue.m_data[3] + m_data[5] * rvalue.m_data[7] + m_data[6] * rvalue.m_data[11] + m_data[7] * rvalue.m_data[15];

		result.m_data[8] = m_data[8] * rvalue.m_data[0] + m_data[9] * rvalue.m_data[4] + m_data[10] * rvalue.m_data[8] + m_data[11] * rvalue.m_data[12];
		result.m_data[9] = m_data[8] * rvalue.m_data[1] + m_data[9] * rvalue.m_data[5] + m_data[10] * rvalue.m_data[9] + m_data[11] * rvalue.m_data[13];
		result.m_data[10] = m_data[8] * rvalue.m_data[2] + m_data[9] * rvalue.m_data[6] + m_data[10] * rvalue.m_data[10] + m_data[11] * rvalue.m_data[14];
		result.m_data[11] = m_data[8] * rvalue.m_data[3] + m_data[9] * rvalue.m_data[7] + m_data[10] * rvalue.m_data[11] + m_data[11] * rvalue.m_data[15];

		result.m_data[12] = m_data[12] * rvalue.m_data[0] + m_data[13] * rvalue.m_data[4] + m_data[14] * rvalue.m_data[8] + m_data[15] * rvalue.m_data[12];
		result.m_data[13] = m_data[12] * rvalue.m_data[1] + m_data[13] * rvalue.m_data[5] + m_data[14] * rvalue.m_data[9] + m_data[15] * rvalue.m_data[13];
		result.m_data[14] = m_data[12] * rvalue.m_data[2] + m_data[13] * rvalue.m_data[6] + m_data[14] * rvalue.m_data[10] + m_data[15] * rvalue.m_data[14];
		result.m_data[15] = m_data[12] * rvalue.m_data[3] + m_data[13] * rvalue.m_data[7] + m_data[14] * rvalue.m_data[11] + m_data[15] * rvalue.m_data[15];

		return result;
	}

	Vec4<TYPENAME> operator*(const Vec4<TYPENAME>& rvalue) {
		Vec4<TYPENAME> result;

		result.x = m_data[0] * rvalue.x + m_data[1] * rvalue.y + m_data[2] * rvalue.z + m_data[3] * rvalue.w;
		result.y = m_data[4] * rvalue.x + m_data[5] * rvalue.y + m_data[6] * rvalue.z + m_data[7] * rvalue.w;
		result.z = m_data[8] * rvalue.x + m_data[9] * rvalue.y + m_data[10] * rvalue.z + m_data[11] * rvalue.w;
		result.w = m_data[12] * rvalue.x + m_data[13] * rvalue.y + m_data[14] * rvalue.z + m_data[15] * rvalue.w;

		return result;
	}
};


#endif//__2022_01_05_MATRIX_4_4_H__