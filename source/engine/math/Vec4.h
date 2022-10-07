/*
	��������������

	������ֻ�ܺ;������   Vec*Mat

	������ֻ�ܺ;����ҳ�   Mat*Vec

	
*/
#ifndef __2022_01_05_MATH_VEC4_H__
#define __2022_01_05_MATH_VEC4_H__

#include "define.h"

BEGIN_NAMESPACE

//������
template<class TYPENAME>
class Vec4
{
public:
	union 
	{
		struct  
		{
			TYPENAME x;
			TYPENAME y;
			TYPENAME z;
			TYPENAME w;
		};

		struct
		{
			TYPENAME r;
			TYPENAME g;
			TYPENAME b;
			TYPENAME a;
		};
	};
	
public:
	Vec4() {

	}

	Vec4(TYPENAME x, TYPENAME y, TYPENAME z, TYPENAME w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
};


typedef Vec4<float>		fVec4;
typedef Vec4<int>		iVec4;

END_NAMESPACE

#endif//__2022_01_05_MATH_VEC4_H__