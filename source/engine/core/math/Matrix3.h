#pragma once
/*
	¡–æÿ’Û
*/

#include "define.h"

BEGIN_OGS_NAMESPACE

class Matrix3
{
public:
	static const Matrix3& Identity();
	Matrix3();
private:
	union
	{
		struct  
		{
			float _11, _21, _31;
			float _12, _22, _32;
			float _13, _23, _33;
		};
		float values[9];
	};
};
END_OGS_NAMESPACE