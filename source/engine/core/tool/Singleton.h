#pragma once

#include "common.h"

BEGIN_OGS_NAMESPACE

template<typename T>
class Singleton
{
private:
	static T* s_instance;
public:
	static T* getInstance()
	{
		if (s_instance == nullptr)
		{
			s_instance = new T();
		}
		return s_instance;
	}

	static void DestroyInstance()
	{
		delete s_instance;
		s_instance = nullptr;
	}
};

template<typename T>
T* Singleton<T>::s_instance = nullptr;

END_OGS_NAMESPACE