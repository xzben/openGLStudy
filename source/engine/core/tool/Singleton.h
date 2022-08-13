#pragma once

#include "common.h"

BEGIN_OGS_NAMESPACE

template<typename T>
class Singleton
{
public:
	static T* s_instance;
	static T* getInstance()
	{
		if (s_instance == nullptr)
		{
			s_instance = new T();
			auto ptr = dynamic_cast<Singleton*>(s_instance);
			ptr->init();
		}

		return s_instance;
	}
protected:
	virtual bool init() = 0;
};

template<typename T> T* Singleton<T>::s_instance = nullptr;

END_OGS_NAMESPACE