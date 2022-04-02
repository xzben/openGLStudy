#ifndef __2022_04_01_INSTANCE_BASE_H__
#define __2022_04_01_INSTANCE_BASE_H__

#include "common.h"

BEGIN_NAMESPACE

template<class ClsName>
class InstanceBase
{
protected:
	static ClsName* s_instance;;
public:

	static ClsName* getInstance()
	{
		if (s_instance == nullptr)
		{
			s_instance = new ClsName();
		}

		return s_instance;
	}

	static void destroyInstance()
	{
		if (s_instance)
		{
			delete s_instance;
		}
		s_instance = nullptr;
	}
};

template<class ClsName> ClsName* InstanceBase<ClsName>::s_instance = nullptr;

END_NAMESPACE

#endif//__2022_04_01_INSTANCE_BASE_H__