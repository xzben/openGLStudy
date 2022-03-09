#ifndef __2022_01_05_MATRIX_3_3_H__
#define __2022_01_05_MATRIX_3_3_H__

#include "Vec3.h"

template<class TYPENAME>
class Mat3
{
public:
	TYPENAME m_data[9];

	Mat3() {
		m_data[0] = 1;
		m_data[1] = 0;
		m_data[2] = 0;

		m_data[3] = 0;
		m_data[4] = 1;
		m_data[5] = 0;

		m_data[6] = 0;
		m_data[7] = 0;
		m_data[8] = 1;
		
	}

	~Mat3() {

	}

	void operator+(const TYPENAME& val) {
		for (int i = 0; i < 9; i++)
			m_data[i] += val;
	}

	void operator-(const TYPENAME& val) {
		for (int i = 0; i < 9; i++)
			m_data[i] -= val;
	}

	void operator*(const TYPENAME& val) {
		for (int i = 0; i < 9; i++)
			m_data[i] *= val;
	}

	Mat3<TYPENAME> operator*(const Mat3<TYPENAME>& rvalue) {
		Mat3<TYPENAME> result;

		result.m_data[0] = m_data[0] * rvalue.m_data[0] + m_data[1] * rvalue.m_data[3] + m_data[2] * rvalue.m_data[6];
		result.m_data[1] = m_data[0] * rvalue.m_data[1] + m_data[1] * rvalue.m_data[4] + m_data[2] * rvalue.m_data[7];
		result.m_data[2] = m_data[0] * rvalue.m_data[2] + m_data[1] * rvalue.m_data[5] + m_data[2] * rvalue.m_data[8];

		result.m_data[3] = m_data[3] * rvalue.m_data[0] + m_data[4] * rvalue.m_data[3] + m_data[5] * rvalue.m_data[6];
		result.m_data[4] = m_data[3] * rvalue.m_data[1] + m_data[4] * rvalue.m_data[4] + m_data[5] * rvalue.m_data[7];
		result.m_data[5] = m_data[3] * rvalue.m_data[2] + m_data[4] * rvalue.m_data[5] + m_data[5] * rvalue.m_data[8];

		result.m_data[6] = m_data[6] * rvalue.m_data[0] + m_data[7] * rvalue.m_data[3] + m_data[8] * rvalue.m_data[6];
		result.m_data[7] = m_data[6] * rvalue.m_data[1] + m_data[7] * rvalue.m_data[4] + m_data[8] * rvalue.m_data[7];
		result.m_data[8] = m_data[6] * rvalue.m_data[2] + m_data[7] * rvalue.m_data[5] + m_data[8] * rvalue.m_data[8];

		return result;
	}

	Vec3<TYPENAME> operator*(const Vec3<TYPENAME>& rvalue) {
		Vec3<TYPENAME> result;

		result.x = m_data[0] * rvalue.x + m_data[1] * rvalue.y + m_data[2] * rvalue.z;
		result.y = m_data[3] * rvalue.x + m_data[4] * rvalue.y + m_data[5] * rvalue.z;
		result.z = m_data[6] * rvalue.x + m_data[7] * rvalue.y + m_data[8] * rvalue.z;

		return result;
	}
};

typedef Mat3<float> fMat3;
typedef Mat3<int> iMat3;

#endif//__2022_01_05_MATRIX_3_3_H__