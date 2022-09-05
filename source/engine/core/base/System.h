#pragma once

#include "common.h"
#include "Object.h"
#include <string>

BEGIN_OGS_NAMESPACE

class System : public Object, public NoCopy
{
public:
	explicit System(std::string& name);

	virtual ~System() {};

public:
	virtual bool init() { return true; };
	virtual void update(float dt) {};
	virtual void destroy() {};
private:
	std::string m_name = std::string("");
	int  m_prority = 0;  //”≈œ»º∂
};

END_OGS_NAMESPACE