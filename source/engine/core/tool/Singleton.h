#pragma once

#include "common.h"

BEGIN_OGS_NAMESPACE

template<typename T>
class Singleton
{
public:
	static T* GetInstance()
	{
		static T s_instance;
		return &s_instance;
	}
};

END_OGS_NAMESPACE