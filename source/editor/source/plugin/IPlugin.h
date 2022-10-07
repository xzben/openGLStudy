#pragma once

#include "editor_define.h"

BEGIN_EDITOR_NAMESPACE

class IPlugin
{
public:
	virtual void excute() = 0;
	void* userData{ nullptr };
};

END_EDITOR_NAMESPACE