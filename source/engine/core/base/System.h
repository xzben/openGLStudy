#pragma once

#include "define.h"
#include "Object.h"
#include <string>

BEGIN_OGS_NAMESPACE

class System : public Object
{
	DECLARE_RUNTIME_CLASS(System)
public:
	System(std::string& name);
	System(){}
	virtual ~System() {};
public:
	virtual void update(float dt) {};
	virtual void destroy() {};
protected:
	std::string m_name{ "" };
	int  m_prority{ 0 };  //”≈œ»º∂
};

END_OGS_NAMESPACE