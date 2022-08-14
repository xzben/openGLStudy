#pragma once

#include "common.h"

BEGIN_OGS_NAMESPACE

template<typename T>
class Singleton
{
public:
	static T* s_instance;
	static T* GetInstance()
	{
		if (s_instance == nullptr)
		{
			s_instance = new T();
		}

		return s_instance;
	}
};

template<typename T> T* Singleton<T>::s_instance = nullptr;

END_OGS_NAMESPACE